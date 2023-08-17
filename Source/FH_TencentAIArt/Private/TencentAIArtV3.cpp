#include "TencentAIArtV3.h"
#include <iomanip>
#include <sstream>
#include <stdio.h>
#include <time.h>

#define UI UI_ST
THIRD_PARTY_INCLUDES_START
#include "openssl/sha.h"
#include "openssl/hmac.h"
THIRD_PARTY_INCLUDES_END
#undef UI

void TencentAIArtV3::initConfig(const FTencentAIArtConfig& AIArtConfig)
{
	SECRET_ID = TCHAR_TO_UTF8(*AIArtConfig.Secret_ID);
	SECRET_KEY =  TCHAR_TO_UTF8(*AIArtConfig.Secret_Key);
	service =  TCHAR_TO_UTF8(*AIArtConfig.Service);
	host =  TCHAR_TO_UTF8(*UTencentConfig::ConvStr_EHost(AIArtConfig.Host));
	region =  TCHAR_TO_UTF8(*UTencentConfig::ConvStr_Region(AIArtConfig.Region));
	action =  TCHAR_TO_UTF8(*UTencentConfig::ConvStr_EAction(AIArtConfig.Action));
	version =  TCHAR_TO_UTF8(*AIArtConfig.Version);
}

void TencentAIArtV3::initTTI_Or_ITI(const FPromptTTIConfig& PromptTTIConfig)
{
	const FString TTI_Prompt = PromptTTIConfig.Prompt;
	const FString TTI_Styles = UTencentConfig::ConvStr_EStylesTTI(PromptTTIConfig.Styles);
	const FString TTI_Resolution = UTencentConfig::ConvStr_EResolution(PromptTTIConfig.Resolution);
	const int TTI_LogoAdd = UTencentConfig::ConvStr_ELogoAdd(PromptTTIConfig.LogoAdd);
	ReqImageType = PromptTTIConfig.ReqImgType;
	const FString TTI_ReqImgType = UTencentConfig::ConvStr_ERspImgType(ReqImageType);
	const FString Text =
		FString::Printf(
			TEXT("{\"Prompt\":\"%s\",\"Styles\":[\"%s\"],\"ResultConfig\":{\"Resolution\":\"%s\"},\"LogoAdd\":%d,\"RspImgType\":\"%s\"}"),
			*TTI_Prompt, *TTI_Styles, *TTI_Resolution, TTI_LogoAdd, *TTI_ReqImgType);
	
	payload = string(TCHAR_TO_UTF8(*Text));
	UE_LOG(LogTencentAIArt, Warning, TEXT("payload = %s"), *FString(UTF8_TO_TCHAR(payload.c_str())));
}

void TencentAIArtV3::getReqImageType(EReqImgType& ReqImgType) const
{
	ReqImgType = ReqImageType;
}

string TencentAIArtV3::get_data(const int64_t& Timestamp)
{
	char buff[20] = {0};
	tm sttime;
	gmtime_s(&sttime, &Timestamp);
	strftime(buff, sizeof(buff), "%Y-%m-%d", &sttime);
	string utcDate = string(buff);
	return utcDate;
}

string TencentAIArtV3::int2str(const int64_t n)
{
	std::stringstream ss;
	ss << n;
	return ss.str();
}

string TencentAIArtV3::sha256Hex(const string& str)
{
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, str.c_str(), str.size());
	SHA256_Final(hash, &sha256);
	std::string NewString = "";
	for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		char buf[3];
		snprintf(buf, sizeof(buf), "%02x", hash[i]);
		NewString = NewString + buf;
	}
	return NewString;
}

string TencentAIArtV3::HmacSha256(const string& key, const string& input)
{
	unsigned char hash[32];

	HMAC_CTX *h;
#if OPENSSL_VERSION_NUMBER < 0x10100000L
	HMAC_CTX hmac;
	HMAC_CTX_init(&hmac);
	h = &hmac;
#else
	h = HMAC_CTX_new();
#endif

	HMAC_Init_ex(h, &key[0], key.length(), EVP_sha256(), nullptr);
	HMAC_Update(h, ( unsigned char* )&input[0], input.length());
	unsigned int len = 32;
	HMAC_Final(h, hash, &len);

#if OPENSSL_VERSION_NUMBER < 0x10100000L
	HMAC_CTX_cleanup(h);
#else
	HMAC_CTX_free(h);
#endif

	std::stringstream ss;
	ss << std::setfill('0');
	for (unsigned int i = 0; i < len; i++)
	{
		ss  << hash[i];
	}
	return (ss.str());
}

string TencentAIArtV3::HexEncode(const string& input)
{
	const size_t len = input.length();

	string output;
	output.reserve(2 * len);
	for (size_t i = 0; i < len; ++i)
	{
		static const char* const lut = "0123456789abcdef";
		const unsigned char c = input[i];
		output.push_back(lut[c >> 4]);
		output.push_back(lut[c & 15]);
	}
	return output;
}

string TencentAIArtV3::GetAuthorization()
{
	timestamp = FDateTime::UtcNow().ToUnixTimestamp();
	date = get_data(timestamp);
	
	// ************* 步骤 1：拼接规范请求串 *************
	hashedRequestPayload = sha256Hex(payload);
	UE_LOG(LogTencentAIArt, Warning, TEXT("hashedRequestPayload = %s"), *FString(hashedRequestPayload.c_str()))

	httpRequestMethod = "POST";
	canonicalUri = "/";
	canonicalQueryString = "";
	lower = action;
	std::transform(action.begin(), action.end(), lower.begin(), ::tolower);
	canonicalHeaders = string("content-type:application/json\n")
			+ "host:" + host + "\n"
			+ "x-tc-action:" + lower + "\n";
	signedHeaders = "content-type;host;x-tc-action";
	canonicalRequest = httpRequestMethod + "\n"
			+ canonicalUri + "\n"
			+ canonicalQueryString + "\n"
			+ canonicalHeaders + "\n"
			+ signedHeaders + "\n"
			+ hashedRequestPayload;

	UE_LOG(LogTencentAIArt, Warning, TEXT("canonicalRequest = %s"), *FString(canonicalRequest.c_str()))

	// ************* 步骤 2：拼接待签名字符串 *************
	algorithm = "TC3-HMAC-SHA256";
	RequestTimestamp = int2str(timestamp);
	credentialScope = date + "/" + service + "/" + "tc3_request";
	hashedCanonicalRequest = sha256Hex(canonicalRequest);
	stringToSign = algorithm + "\n" + RequestTimestamp + "\n" + credentialScope + "\n" + hashedCanonicalRequest;

	UE_LOG(LogTencentAIArt, Warning, TEXT("stringToSign = %s"), *FString(stringToSign.c_str()))

	// ************* 步骤 3：计算签名 ***************
	kKey = "TC3" + SECRET_KEY;
	kDate = HmacSha256(kKey, date);
	kService = HmacSha256(kDate, service);
	kSigning = HmacSha256(kService, "tc3_request");
	signature = HexEncode(HmacSha256(kSigning, stringToSign));

	// ************* 步骤 4：拼接 Authorization *************
	authorization = algorithm + " " + "Credential=" + SECRET_ID + "/" + credentialScope + ", "
			+ "SignedHeaders=" + signedHeaders + ", " + "Signature=" + signature;

	UE_LOG(LogTencentAIArt, Warning, TEXT("authorization = %s"), *FString(authorization.c_str()))
	
	return authorization;
}
