#pragma once
#include "ImageUtils.h"
#include "TencentAIArtConfig.generated.h"

// Region
UENUM(BlueprintType)
enum class ERegion : uint8
{
	ER_ShangHai		UMETA(Displayname="ap-shanghai"),
	ER_GuangZhou	UMETA(Displayname="ap-guangzhou")
};

// Host
UENUM(BlueprintType)
enum class EHost : uint8
{
	EH_Default				UMETA(Displayname="aiart.tencentcloudapi.com"),
	EH_AP_GuangZhou			UMETA(Displayname="(广州)aiart.ap-guangzhou.tencentcloudapi.com"),
	EH_AP_ShangHai			UMETA(Displayname="(上海)aiart.ap-shanghai.tencentcloudapi.com"),
	EH_AP_BeiJing			UMETA(Displayname="(北京)aiart.ap-beijing.tencentcloudapi.com"),
	EH_AP_ChengDu			UMETA(Displayname="(成都)aiart.ap-chengdu.tencentcloudapi.com"),
	EH_AP_ChongQing			UMETA(Displayname="(重庆)aiart.ap-chongqing.tencentcloudapi.com"),
	EH_AP_HongKong			UMETA(Displayname="(中国香港)aiart.ap-hongkong.tencentcloudapi.com"),
	EH_AP_Singapore			UMETA(Displayname="(新加坡)aiart.ap-singapore.tencentcloudapi.com"),
	EH_AP_Bangkok			UMETA(Displayname="(曼谷)aiart.ap-bangkok.tencentcloudapi.com"),
	EH_AP_Mumbai			UMETA(Displayname="(孟买)aiart.ap-mumbai.tencentcloudapi.com"),
	EH_AP_Seoul				UMETA(Displayname="(首尔)aiart.ap-seoul.tencentcloudapi.com"),
	EH_AP_Tokyo				UMETA(Displayname="(东京)aiart.ap-tokyo.tencentcloudapi.com"),
	EH_NA_Ashburn			UMETA(Displayname="(弗吉尼亚)aiart.na-ashburn.tencentcloudapi.com"),
	EH_NA_Siliconvalley		UMETA(Displayname="(硅谷)aiart.na-siliconvalley.tencentcloudapi.com"),
	EH_NA_Toronto			UMETA(Displayname="(多伦多)aiart.na-toronto.tencentcloudapi.com"),
	EH_EU_Frankfurt			UMETA(Displayname="(法兰克福)aiart.eu-frankfurt.tencentcloudapi.com")
};

// Action
UENUM(BlueprintType)
enum class EAction : uint8
{
	EA_TTI	UMETA(Displayname="TextToImage"),
	EA_ITI	UMETA(Displayname="ImageToImage")
};

// Style
UENUM(BlueprintType)
enum class EStylesTTI : uint8
{
	ESTTI_101	UMETA(Displayname="(水墨画)-101"),
	ESTTI_102	UMETA(Displayname="(概念艺术)-102"),
	ESTTI_103	UMETA(Displayname="(油画)-103"),
	ESTTI_104	UMETA(Displayname="(水彩画)-104"),
	ESTTI_106	UMETA(Displayname="(厚涂风格)-106"),
	ESTTI_107	UMETA(Displayname="(插图)-107"),
	ESTTI_108	UMETA(Displayname="(剪纸风格)-108"),
	ESTTI_109	UMETA(Displayname="(印象派)-109"),
	ESTTI_110	UMETA(Displayname="(2.5D)-110"),
	ESTTI_111	UMETA(Displayname="(肖像画)-111"),
	ESTTI_112	UMETA(Displayname="(黑白素描画)-112"),
	ESTTI_113	UMETA(Displayname="(赛博朋克)-113"),
	ESTTI_114	UMETA(Displayname="(科幻风格)-114"),
	ESTTI_115	UMETA(Displayname="(暗黑风格)-115"),
	ESTTI_201	UMETA(Displayname="(日系动漫)-201"),
	ESTTI_202	UMETA(Displayname="(怪兽风格)-202"),
	ESTTI_301	UMETA(Displayname="(游戏卡通手绘)-301"),
	ESTTI_401	UMETA(Displayname="(通用写实风格)-401")
};

UENUM(BlueprintType)
enum class EStylesITI : uint8
{
	ESITI_106	UMETA(Displayname="(水彩画)-106"),
	ESITI_110	UMETA(Displayname="(2.5D)-110"),
	ESITI_201	UMETA(Displayname="(日系动漫)-201"),
	ESITI_202	UMETA(Displayname="(美系动漫)-202"),
	ESITI_203	UMETA(Displayname="(唯美古风)-203")
};

// Resolution
UENUM(BlueprintType)
enum class EResolution : uint8
{
	ER_768_768		UMETA(Displayname="768:768"),
	ER_768_1024		UMETA(Displayname="768:1024"),
	ER_1024_768		UMETA(Displayname="1024:768")
};

// LogoAdd
UENUM(BlueprintType)
enum class ELogoAdd : uint8
{
	ELA_NoAdd	UMETA(Displayname="Logo_No"),
	ELA_Add		UMETA(Displayname="Logo_Add")
};

// RspImgType
UENUM(BlueprintType)
enum class EReqImgType : uint8
{
	EReqType_Base64		UMETA(Displayname="base64"),
	EReqType_URL		UMETA(Displayname="url")
};

// Struct
USTRUCT(BlueprintType)
struct FTencentAIArtConfig
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category="FH|TencentAIArt|Config")
	FString Secret_ID;
	UPROPERTY(BlueprintReadWrite, Category="FH|TencentAIArt|Config")
	FString Secret_Key;
	UPROPERTY(BlueprintReadWrite, Category="FH|TencentAIArt|Config")
	FString Service;
	UPROPERTY(BlueprintReadWrite, Category="FH|TencentAIArt|Config")
	EHost Host;
	UPROPERTY(BlueprintReadWrite, Category="FH|TencentAIArt|Config")
	ERegion Region;
	UPROPERTY(BlueprintReadWrite, Category="FH|TencentAIArt|Config")
	EAction Action;
	UPROPERTY(BlueprintReadWrite, Category="FH|TencentAIArt|Config")
	FString Version;
	
	FTencentAIArtConfig() :
		Service("aiart"),
		Host(EHost::EH_AP_ShangHai),
		Region(ERegion::ER_ShangHai),
		Action(EAction::EA_TTI),
		Version("2022-12-29"){}
};

USTRUCT(BlueprintType)
struct FPromptTTIConfig
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category="FH|TencentAIArt|Prompt")
	FString Prompt;
	UPROPERTY(BlueprintReadWrite, Category="FH|TencentAIArt|Prompt")
	EStylesTTI Styles;
	UPROPERTY(BlueprintReadWrite, Category="FH|TencentAIArt|Prompt")
	EResolution Resolution;
	UPROPERTY(BlueprintReadWrite, Category="FH|TencentAIArt|Prompt")
	ELogoAdd LogoAdd;
	UPROPERTY(BlueprintReadWrite, Category="FH|TencentAIArt|Prompt")
	EReqImgType ReqImgType;

	FPromptTTIConfig() :
		Styles(EStylesTTI::ESTTI_201),
		Resolution(EResolution::ER_768_768),
		LogoAdd(ELogoAdd::ELA_NoAdd),
		ReqImgType(EReqImgType::EReqType_Base64){}
};

UCLASS(BlueprintType)
class UTencentConfig : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="FH|Tencent|AI Art|Conv")
	static FORCEINLINE FString ConvStr_Region(const ERegion& Region)
	{
		auto Result =
			Region ==
				ERegion::ER_ShangHai ? FString("ap-shanghai") :
			Region ==
				ERegion::ER_GuangZhou ? FString("ap-guangzhou") : FString("ap-shanghai");
		return Result;
	}

	UFUNCTION(BlueprintCallable, Category="FH|Tencent|AI Art|Conv")
	static FORCEINLINE FString ConvStr_EHost(const EHost& Host)
	{
		FString Result = "aiart.tencentcloudapi.com";
		switch (Host)
		{
		case EHost::EH_Default: return Result;
		case EHost::EH_AP_GuangZhou: Result = "aiart.ap-guangzhou.tencentcloudapi.com"; return Result;
		case EHost::EH_AP_ShangHai: Result = "aiart.ap-shanghai.tencentcloudapi.com"; return Result;
		case EHost::EH_AP_BeiJing: Result = "aiart.ap-beijing.tencentcloudapi.com"; return Result;
		case EHost::EH_AP_ChengDu: Result = "aiart.ap-chengdu.tencentcloudapi.com"; return Result;
		case EHost::EH_AP_ChongQing: Result = "aiart.ap-chongqing.tencentcloudapi.com"; return Result;
		case EHost::EH_AP_HongKong: Result = "aiart.ap-hongkong.tencentcloudapi.com"; return Result;
		case EHost::EH_AP_Singapore: Result = "aiart.ap-singapore.tencentcloudapi.com"; return Result;
		case EHost::EH_AP_Bangkok: Result = "aiart.ap-bangkok.tencentcloudapi.com"; return Result;
		case EHost::EH_AP_Mumbai: Result = "aiart.ap-mumbai.tencentcloudapi.com"; return Result;
		case EHost::EH_AP_Seoul: Result = "aiart.ap-seoul.tencentcloudapi.com"; return Result;
		case EHost::EH_AP_Tokyo: Result = "aiart.ap-tokyo.tencentcloudapi.com"; return Result;
		case EHost::EH_NA_Ashburn: Result = "aiart.na-ashburn.tencentcloudapi.com"; return Result;
		case EHost::EH_NA_Siliconvalley: Result = "aiart.na-siliconvalley.tencentcloudapi.com"; return Result;
		case EHost::EH_NA_Toronto: Result = "aiart.na-toronto.tencentcloudapi.com"; return Result;
		case EHost::EH_EU_Frankfurt: Result = "aiart.eu-frankfurt.tencentcloudapi.com"; return Result;
		default: return Result;
		}
	}

	UFUNCTION(BlueprintCallable, Category="FH|Tencent|AI Art|Conv")
	static FORCEINLINE FString ConvStr_EAction(const EAction& Action)
	{
		auto Result =
			Action ==
				EAction::EA_TTI ? FString("texttoimage") :
			Action ==
				EAction::EA_ITI ? FString("imagetoimage") : FString("texttoimage");
		return Result;
	}

	UFUNCTION(BlueprintCallable, Category="FH|Tencent|AI Art|Conv")
	static FORCEINLINE FString ConvStr_EStylesTTI(const EStylesTTI& StylesTTI)
	{
		FString Result = "201";
		switch (StylesTTI)
		{
		case EStylesTTI::ESTTI_101: Result = "101"; return Result;
		case EStylesTTI::ESTTI_102: Result = "102"; return Result;
		case EStylesTTI::ESTTI_103: Result = "103"; return Result;
		case EStylesTTI::ESTTI_104: Result = "104"; return Result;
		case EStylesTTI::ESTTI_106: Result = "106"; return Result;
		case EStylesTTI::ESTTI_107: Result = "107"; return Result;
		case EStylesTTI::ESTTI_108: Result = "108"; return Result;
		case EStylesTTI::ESTTI_109: Result = "109"; return Result;
		case EStylesTTI::ESTTI_110: Result = "110"; return Result;
		case EStylesTTI::ESTTI_111: Result = "111"; return Result;
		case EStylesTTI::ESTTI_112: Result = "112"; return Result;
		case EStylesTTI::ESTTI_113: Result = "113"; return Result;
		case EStylesTTI::ESTTI_114: Result = "114"; return Result;
		case EStylesTTI::ESTTI_115: Result = "115"; return Result;
		case EStylesTTI::ESTTI_201: Result = "201"; return Result;
		case EStylesTTI::ESTTI_202: Result = "202"; return Result;
		case EStylesTTI::ESTTI_301: Result = "301"; return Result;
		case EStylesTTI::ESTTI_401: Result = "401"; return Result;
		default: return Result;
		}
	}

	UFUNCTION(BlueprintCallable, Category="FH|Tencent|AI Art|Conv")
	static FORCEINLINE EStylesTTI ConvEnum_EStyleTTI(FString Style)
	{
		auto EStyle = EStylesTTI::ESTTI_201;
		if (Style.Equals(TEXT("(水墨画)-101"), ESearchCase::IgnoreCase) || Style.Equals(TEXT("水墨画"), ESearchCase::IgnoreCase)) {EStyle = EStylesTTI::ESTTI_101;}
		if (Style.Equals(TEXT("(概念艺术)-102"), ESearchCase::IgnoreCase) || Style.Equals(TEXT("概念艺术"), ESearchCase::IgnoreCase)) {EStyle = EStylesTTI::ESTTI_102;}
		if (Style.Equals(TEXT("(油画)-103"), ESearchCase::IgnoreCase) || Style.Equals(TEXT("油画"), ESearchCase::IgnoreCase)) {EStyle = EStylesTTI::ESTTI_103;}
		if (Style.Equals(TEXT("(水彩画)-104"), ESearchCase::IgnoreCase) || Style.Equals(TEXT("水彩画"), ESearchCase::IgnoreCase)) {EStyle = EStylesTTI::ESTTI_104;}
		if (Style.Equals(TEXT("(厚涂风格)-106"), ESearchCase::IgnoreCase) || Style.Equals(TEXT("厚涂风格"), ESearchCase::IgnoreCase)) {EStyle = EStylesTTI::ESTTI_106;}
		if (Style.Equals(TEXT("(插图)-107"), ESearchCase::IgnoreCase) || Style.Equals(TEXT("插图"), ESearchCase::IgnoreCase)) {EStyle = EStylesTTI::ESTTI_107;}
		if (Style.Equals(TEXT("(剪纸风格)-108"), ESearchCase::IgnoreCase) || Style.Equals(TEXT("剪纸风格"), ESearchCase::IgnoreCase)) {EStyle = EStylesTTI::ESTTI_108;}
		if (Style.Equals(TEXT("(印象派)-109"), ESearchCase::IgnoreCase) || Style.Equals(TEXT("印象派"), ESearchCase::IgnoreCase)) {EStyle = EStylesTTI::ESTTI_109;}
		if (Style.Equals(TEXT("(2.5D)-110"), ESearchCase::IgnoreCase) || Style.Equals(TEXT("2.5D"), ESearchCase::IgnoreCase)) {EStyle = EStylesTTI::ESTTI_110;}
		if (Style.Equals(TEXT("(肖像画)-111"), ESearchCase::IgnoreCase) || Style.Equals(TEXT("肖像画"), ESearchCase::IgnoreCase)) {EStyle = EStylesTTI::ESTTI_111;}
		if (Style.Equals(TEXT("(黑白素描画)-112"), ESearchCase::IgnoreCase) || Style.Equals(TEXT("黑白素描画"), ESearchCase::IgnoreCase)) {EStyle = EStylesTTI::ESTTI_112;}
		if (Style.Equals(TEXT("(赛博朋克)-113"), ESearchCase::IgnoreCase) || Style.Equals(TEXT("赛博朋克"), ESearchCase::IgnoreCase)) {EStyle = EStylesTTI::ESTTI_113;}
		if (Style.Equals(TEXT("(科幻风格)-114"), ESearchCase::IgnoreCase) || Style.Equals(TEXT("科幻风格"), ESearchCase::IgnoreCase)) {EStyle = EStylesTTI::ESTTI_114;}
		if (Style.Equals(TEXT("(暗黑风格)-115"), ESearchCase::IgnoreCase) || Style.Equals(TEXT("暗黑风格"), ESearchCase::IgnoreCase)) {EStyle = EStylesTTI::ESTTI_115;}
		if (Style.Equals(TEXT("(日系动漫)-201"), ESearchCase::IgnoreCase) || Style.Equals(TEXT("日系动漫"), ESearchCase::IgnoreCase)) {EStyle = EStylesTTI::ESTTI_201;}
		if (Style.Equals(TEXT("(怪兽风格)-202"), ESearchCase::IgnoreCase) || Style.Equals(TEXT("怪兽风格"), ESearchCase::IgnoreCase)) {EStyle = EStylesTTI::ESTTI_202;}
		if (Style.Equals(TEXT("(游戏卡通手绘)-301"), ESearchCase::IgnoreCase) || Style.Equals(TEXT("游戏卡通手绘"), ESearchCase::IgnoreCase)) {EStyle = EStylesTTI::ESTTI_301;}
		if (Style.Equals(TEXT("(通用写实风格)-401"), ESearchCase::IgnoreCase) || Style.Equals(TEXT("通用写实风格"), ESearchCase::IgnoreCase)) {EStyle = EStylesTTI::ESTTI_401;}
		return EStyle;
	}

	UFUNCTION(BlueprintCallable, Category="FH|Tencent|AI Art|Conv")
	static FORCEINLINE FString ConvDisplayName_EStyleTTI(EStylesTTI Style)
	{
		if (Style == EStylesTTI::ESTTI_101) return TEXT("水墨画");
		if (Style == EStylesTTI::ESTTI_102) return TEXT("概念艺术");
		if (Style == EStylesTTI::ESTTI_103) return TEXT("油画");
		if (Style == EStylesTTI::ESTTI_104) return TEXT("水彩画");
		if (Style == EStylesTTI::ESTTI_106) return TEXT("厚涂风格");
		if (Style == EStylesTTI::ESTTI_107) return TEXT("插图");
		if (Style == EStylesTTI::ESTTI_108) return TEXT("剪纸风格");
		if (Style == EStylesTTI::ESTTI_109) return TEXT("印象派");
		if (Style == EStylesTTI::ESTTI_110) return TEXT("2.5D");
		if (Style == EStylesTTI::ESTTI_111) return TEXT("肖像画");
		if (Style == EStylesTTI::ESTTI_112) return TEXT("黑白素描画");
		if (Style == EStylesTTI::ESTTI_113) return TEXT("赛博朋克");
		if (Style == EStylesTTI::ESTTI_114) return TEXT("科幻风格");
		if (Style == EStylesTTI::ESTTI_115) return TEXT("暗黑风格");
		if (Style == EStylesTTI::ESTTI_201) return TEXT("日系动漫");
		if (Style == EStylesTTI::ESTTI_202) return TEXT("怪兽风格");
		if (Style == EStylesTTI::ESTTI_301) return TEXT("游戏卡通手绘");
		if (Style == EStylesTTI::ESTTI_401) return TEXT("通用写实风格");
		return TEXT("日系动漫");
	}

	UFUNCTION(BlueprintCallable, Category="FH|Tencent|AI Art|Conv")
	static FORCEINLINE FString ConvStr_EStylesITI(const EStylesITI& StylesITI)
	{
		auto Result = FString("201");
		if (StylesITI == EStylesITI::ESITI_106) {Result = "106"; return Result;}
		if (StylesITI == EStylesITI::ESITI_110) {Result = "110"; return Result;}
		if (StylesITI == EStylesITI::ESITI_201) {Result = "201"; return Result;}
		if (StylesITI == EStylesITI::ESITI_202) {Result = "202"; return Result;}
		if (StylesITI == EStylesITI::ESITI_203) {Result = "203"; return Result;}
		return Result;
	}

	UFUNCTION(BlueprintCallable, Category="FH|Tencent|AI Art|Conv")
	static FORCEINLINE FString ConvStr_EResolution(const EResolution& Resolution)
	{
		auto Result = FString("768:768");
		if (Resolution == EResolution::ER_768_768) {Result = "768:768"; return Result;}
		if (Resolution == EResolution::ER_768_1024) {Result = "768:1024"; return Result;}
		if (Resolution == EResolution::ER_1024_768) {Result = "1024:768"; return Result;}
		return Result;
	}

	UFUNCTION(BlueprintCallable, Category="FH|Tencent|AI Art|Conv")
	static FORCEINLINE int ConvStr_ELogoAdd(const ELogoAdd& LogoAdd)
	{
		auto Result = 0;
		if (LogoAdd == ELogoAdd::ELA_NoAdd) {Result = 0; return Result;}
		if (LogoAdd == ELogoAdd::ELA_Add) {Result = 1; return Result;}
		return Result;
	}

	UFUNCTION(BlueprintCallable, Category="FH|Tencent|AI Art|Conv")
	static FORCEINLINE FString ConvStr_ERspImgType(const EReqImgType& ReqImgType)
	{
		auto Result =
			ReqImgType ==
				EReqImgType::EReqType_Base64 ? FString("base64") :
			ReqImgType ==
				EReqImgType::EReqType_URL ? FString("url") : FString("base64");
		return Result;
	}
	
	static FORCEINLINE UTexture2D* Base64ToTexture2D(const FString& BaseStr)
	{
		TArray<uint8> DecodedBytes;
		FBase64::Decode(BaseStr, DecodedBytes);
		return FImageUtils::ImportBufferAsTexture2D(DecodedBytes);
	}
};
