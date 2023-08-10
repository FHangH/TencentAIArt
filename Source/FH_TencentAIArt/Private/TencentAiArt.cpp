#include "TencentAiArt.h"
#include "Interfaces/IHttpResponse.h"
#include "HttpManager.h"
#include "HttpModule.h"
#include "TencentAIArtV3.h"

void UTencentAiArt::InitConfig(const FTencentAIArtConfig& AIArtConfig)
{
	TencentAIArtV3::Get().initConfig(AIArtConfig);
}

void UTencentAiArt::InitTTI_Or_ITI(const FPromptTTIConfig& PromptTTIConfig)
{
	TencentAIArtV3::Get().initTTI_Or_ITI(PromptTTIConfig);
}

UTencentAiArt* UTencentAiArt::ResultImageByRequest(UObject* WorldContextObject)
{
	const auto RequestObject = NewObject<UTencentAiArt>();
	RequestObject->OnResultImageByRequest();
	RequestObject->RegisterWithGameInstance(WorldContextObject);
	AIArtHandler = RequestObject;
	return RequestObject;
}

UTexture2D* UTencentAiArt::Base64ToTexture2D(const FString& Base64Str)
{
	return UTencentConfig::Base64ToTexture2D(Base64Str);
}

void UTencentAiArt::GetRespImageType(ERspImgType& RspImgType)
{
	TencentAIArtV3::Get().getRspImageType(RspImgType);
}

void UTencentAiArt::OnResultImageByRequest()
{
	AddToRoot();
	
	const FString url = "https://" + FString(TencentAIArtV3::Get().GetHost().c_str());

	HttpRequestImage = FHttpModule::Get().CreateRequest();
	HttpRequestImage->SetVerb("POST");
	HttpRequestImage->SetURL(url);
	HttpRequestImage->SetHeader("Authorization", TencentAIArtV3::Get().GetAuthorization().c_str());
	HttpRequestImage->SetHeader("Content-Type", "application/json");
	HttpRequestImage->SetHeader("Host", TencentAIArtV3::Get().GetHost().c_str());

	if (FString(TencentAIArtV3::Get().GetAction().c_str()) == "ImageToImage")
	{
		HttpRequestImage->SetHeader("X-TC-Action", FString("ImageToImage"));
	}
	HttpRequestImage->SetHeader("X-TC-Action", FString("TextToImage"));
	HttpRequestImage->SetHeader("X-TC-Timestamp", TencentAIArtV3::Get().Gettimestamp().c_str());
	HttpRequestImage->SetHeader("X-TC-Version", TencentAIArtV3::Get().GetVersion().c_str());
	HttpRequestImage->SetHeader("X-TC-Region", TencentAIArtV3::Get().GetRegion().c_str());
	HttpRequestImage->SetContentAsString(FString(UTF8_TO_TCHAR(TencentAIArtV3::Get().GetPayload().c_str())));
	
	HttpRequestImage->OnProcessRequestComplete().BindUObject(this, &UTencentAiArt::OnRequestCompleted);
	HttpRequestImage->OnRequestProgress().BindLambda([](FHttpRequestPtr HttpRequest, int32 BytesSent, int32 BytesReceived)
	{
		UE_LOG(LogTencentAIArt, Warning, TEXT("Is Request Process, wait"))
	});
	
	if (HttpRequestImage->ProcessRequest())
	{
		UE_LOG(LogTencentAIArt, Warning, TEXT("====== TencentAIArt Start ======"));
		UE_LOG(LogTencentAIArt, Warning, TEXT("Request Process"));
		FHttpModule::Get().GetHttpManager().Tick(0.f);

		if (HttpRequestImage->GetStatus() == EHttpRequestStatus::Failed)
		{
			OnFail.Broadcast(FString("null"));
			UE_LOG(LogTencentAIArt, Warning, TEXT("Request Failed"));
			UE_LOG(LogTencentAIArt, Warning, TEXT("====== TencentAIArt End ======"));
		}
	}
}

void UTencentAiArt::OnRequestCompleted(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bWasSuccessful)
{
	UE_LOG(LogTencentAIArt, Warning, TEXT("Request Completed"));
	if (bWasSuccessful && HttpResponse.IsValid())
	{
		UE_LOG(LogTencentAIArt, Warning, TEXT("Request Successed"));
		const FString ResponseContent = HttpResponse->GetContentAsString();

		UE_LOG(LogTencentAIArt, Warning, TEXT("Response Content = %s"), *ResponseContent);
		// 解析响应内容
		TSharedPtr<FJsonObject> JsonObject;
		const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(ResponseContent);
		if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
		{
			if (JsonObject->HasField("Response"))
			{
				UE_LOG(LogTencentAIArt, Warning, TEXT("Get Response"));
				const TSharedPtr<FJsonObject> ResponseObject = JsonObject->GetObjectField("Response");
				if (ResponseObject->HasField("ResultImage"))
				{
					UE_LOG(LogTencentAIArt, Warning, TEXT("Get ResultImage"));
					const FString ImageResult = ResponseObject->GetStringField("ResultImage");

					OnCompleted.Broadcast(ImageResult);
					UE_LOG(LogTencentAIArt, Warning, TEXT("Result = %s"), *ImageResult);
					UE_LOG(LogTencentAIArt, Warning, TEXT("====== TencentAIArt End ======"));
				}
				else
				{
					OnFail.Broadcast(FString("null"));
					UE_LOG(LogTencentAIArt, Warning, TEXT("Request Error"));
					UE_LOG(LogTencentAIArt, Warning, TEXT("====== TencentAIArt End ======"));
				}
			}
			else
			{
				OnFail.Broadcast(FString("null"));
				UE_LOG(LogTencentAIArt, Warning, TEXT("Deserialize Error"));
				UE_LOG(LogTencentAIArt, Warning, TEXT("====== TencentAIArt End ======"));
			}
		}
		
		else
		{
			OnFail.Broadcast(FString("null"));
			UE_LOG(LogTencentAIArt, Warning, TEXT("Deserialize Error"));
			UE_LOG(LogTencentAIArt, Warning, TEXT("====== TencentAIArt End ======"));
		}
	}
	else
	{
		OnFail.Broadcast(FString("null"));
		UE_LOG(LogTencentAIArt, Warning, TEXT("Request Error"));
		UE_LOG(LogTencentAIArt, Warning, TEXT("====== TencentAIArt End ======"));
	}

	RemoveFromRoot();
}

void UTencentAiArt::CancelRequestImage()
{
	if (!AIArtHandler || !AIArtHandler->HttpRequestImage) return;
	const auto Status = AIArtHandler->HttpRequestImage->GetStatus();

	if (Status == EHttpRequestStatus::Processing)
	{
		AIArtHandler->HttpRequestImage->CancelRequest();
		AIArtHandler->HttpRequestImage.Reset();
		UE_LOG(LogTencentAIArt, Warning, TEXT("Request Cancle"))
		UE_LOG(LogTencentAIArt, Warning, TEXT("====== TencentAIArt End ======"));
	}
}
