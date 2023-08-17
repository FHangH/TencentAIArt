#pragma once

#include "CoreMinimal.h"
#include "TencentAIArtConfig.h"
#include "Interfaces/IHttpRequest.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "TencentAiArt.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FResponseDelegate, FString, Result);

UCLASS(Blueprintable)
class FH_TENCENTAIART_API UTencentAiArt : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FResponseDelegate OnCompleted;
	
	UPROPERTY(BlueprintAssignable)
	FResponseDelegate OnFail;

	UFUNCTION(BlueprintCallable, Category="FH|Tencent|AI Art")
	static void InitConfig(const FTencentAIArtConfig& AIArtConfig);

	UFUNCTION(BlueprintCallable, Category="FH|Tencent|AI Art")
	static void InitTTI_Or_ITI(const FPromptTTIConfig& PromptTTIConfig);
	//void InitITI(){}

	UFUNCTION(BlueprintCallable, Category="FH|Tencent|AI Art", meta=(BlueprintInternalUseOnly="true", WorldContext = "WorldContextObject"))
	static UTencentAiArt* ResultImageByRequest(UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category="FH|Tencent|AI Art")
	static UTexture2D* Base64ToTexture2D(const FString& Base64Str);

	UFUNCTION(BlueprintPure, Category="FH|Tencent|AI Art")
	static void GetRequestImageType(EReqImgType& ReqImgType);
	
	UFUNCTION(BlueprintCallable, Category="FH|Tencent|AI Art")
	static void CancelRequestImage();

private:
	inline static UTencentAiArt* AIArtHandler = nullptr;
	TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> HttpRequestImage/* = FHttpModule::Get().CreateRequest()*/;
	
	void OnResultImageByRequest();
	void OnRequestCompleted(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bWasSuccessful);
};