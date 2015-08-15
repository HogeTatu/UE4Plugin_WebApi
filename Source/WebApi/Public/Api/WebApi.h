#pragma once

#include "WebApiRequestBodyUrlParameter.h"
#include "WebApiPreFilterInterface.h"
#include "WebApiPostFilterInterface.h"
#include "WebApi.generated.h"

class UWebApiRequestBodyUrlParameter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWebApiRequestStartDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWebApiRequestProgressDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWebApiRequestSuccessedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWebApiRequestFailedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWebApiRequestCompletedDelegate);

UCLASS(ClassGroup=WebApi, BlueprintType, Blueprintable)
class WEBAPI_API UWebApi : public UObject
{
	GENERATED_UCLASS_BODY()

protected:
	// protected variable

	UWebApiRequestBodyUrlParameter* RequestBodyOrg;
	TQueue<IWebApiPreFilterInterface*> PreFilters;
	TQueue<IWebApiPostFilterInterface*> PostFilters;
	FHttpRequestPtr ProcessingRequest;
	UWebApiResponseBodyBase* ResultResponseBody;

private:
	// private variable

	bool bProcessing;
	int32 SentProgress;
	int32 ReceivedProgress;

public:
	// public property

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WebApi")
	FString Url;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WebApi")
	TArray<int32> SuccessResponseCodes;

	UPROPERTY(BlueprintAssignable, Category="WebApi")
	FOnWebApiRequestStartDelegate OnRequestStart;

	UPROPERTY(BlueprintAssignable, Category="WebApi")
	FOnWebApiRequestProgressDelegate OnRequestProgress;

	UPROPERTY(BlueprintAssignable, Category="WebApi")
	FOnWebApiRequestSuccessedDelegate OnRequestSuccessed;

	UPROPERTY(BlueprintAssignable, Category="WebApi")
	FOnWebApiRequestFailedDelegate OnRequestFailed;

	UPROPERTY(BlueprintAssignable, Category="WebApi")
	FOnWebApiRequestCompletedDelegate OnRequestCompleted;

public:
	// public function

	UFUNCTION(BlueprintCallable, Category = "WebApi")
	static UWebApi* CreateWebApi(UClass* Class);

	UFUNCTION(BlueprintCallable, Category="WebApi")
	void SetRequestParameter(const FString& Key, const FString& Value);

	UFUNCTION(BlueprintCallable, Category="WebApi")
	const FString& GetRequestParameter(const FString& Key) const;

	UFUNCTION(BlueprintCallable, Category="WebApi")
	void AddPreFilter(const TScriptInterface<IWebApiPreFilterInterface>& PreFilter);

	UFUNCTION(BlueprintCallable, Category="WebApi")
	void AddPostFilter(const TScriptInterface<IWebApiPostFilterInterface>& PostFilter);

	UFUNCTION(BlueprintNativeEvent, Category="WebApi")
	void OnStartProcessRequest();

	UFUNCTION(BlueprintCallable, Category="WebApi")
	bool ProcessRequest();

	UFUNCTION(BlueprintCallable, Category="WebApi")
	void CancelRequest();

	UFUNCTION(BlueprintPure, Category="WebApi")
	bool IsProcessingRequest() const;

	UFUNCTION(BlueprintPure, Category="WebApi")
	int32 GetSentProgress() const;

	UFUNCTION(BlueprintPure, Category="WebApi")
	int32 GetReceivedProgress() const;

	UFUNCTION(BlueprintPure, Category="WebApi")
	void GetResponseBody(UWebApiResponseBodyBase*& ResponseBody) const;

private:
	// private function

	void OnRequestCompletedInternal(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccessed);
	void OnRequestProgressInternal(FHttpRequestPtr Request, int32 Sent, int32 Received);
};
