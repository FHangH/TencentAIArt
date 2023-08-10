#pragma once

#include "TencentAIArtConfig.h"

using namespace std;

DECLARE_LOG_CATEGORY_EXTERN(LogTencentAIArt, Log, All);
inline DEFINE_LOG_CATEGORY(LogTencentAIArt);

class TencentAIArtV3
{
private:
	TencentAIArtV3() = default;

	string SECRET_ID;
    string SECRET_KEY;
    string service;
    string host;
    string region;
    string action;
    string version;

	string payload;
    int64_t timestamp;
    string date;

    string hashedRequestPayload;
    string httpRequestMethod;
    string canonicalUri;
    string canonicalQueryString;
    string lower;
    string canonicalHeaders;
    string signedHeaders;
    string canonicalRequest;

    string algorithm;
    string RequestTimestamp;
    string credentialScope;
    string hashedCanonicalRequest;
    string stringToSign;


    string kKey;
    string kDate;
    string kService;
    string kSigning;
    string signature;
    string authorization;

	ERspImgType RspImageType;

public:
	static TencentAIArtV3& Get()
	{
		static TencentAIArtV3 TAAV3;
		return TAAV3;
	}

	void initConfig(const FTencentAIArtConfig& AIArtConfig);
	void initTTI_Or_ITI(const FPromptTTIConfig& PromptTTIConfig);
	void getRspImageType(ERspImgType& RspImgType) const;
	
	string get_data(const int64_t &timestamp);

	string int2str(int64_t n);

	string sha256Hex(const string &str);
	
	string HmacSha256(const string &key, const string &input);

	string HexEncode(const string &input);

	string GetPayload() {return payload;}
	string Gettimestamp() {return int2str(timestamp);}
	string GetHost() {return host;}
	string GetAction() {return action;}
	string GetVersion() {return version;}
	string GetRegion() {return region;}
	string GetAuthorization();
};