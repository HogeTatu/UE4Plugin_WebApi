#pragma once

#include "WebApiRequestBodyUrlParameter.h"
#include "WebApiPreFilterInterface.h"
#include "WebApiPostFilterInterface.h"
#include "WebApi.generated.h"

class UWebApiRequestBodyUrlParameter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWebApiRequestStartDelegate, class UWebApi*, Api);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnWebApiRequestProgressDelegate, class UWebApi*, Api, int32, Sent, int32, Received);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWebApiRequestSuccessedDelegate, class UWebApi*, Api, class UWebApiResponseBodyBase*, Response);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWebApiRequestFailedDelegate, class UWebApi*, Api, class UWebApiResponseBodyBase*, Response);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWebApiRequestCompletedDelegate, class UWebApi*, Api, class UWebApiResponseBodyBase*, Response);

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

private:
	// private variable

	bool bProcessing;

public:
	// public property

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WebApi")
	FString Domain;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WebApi")
	FString Path;

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

	UFUNCTION(BlueprintPure, Category="WebApi")
	FString GetRequestURL() const;

	UFUNCTION(BlueprintCallable, Category="WebApi")
	void SetRequestParameter(const FString& Key, const FString& Value);

	UFUNCTION(BlueprintCallable, Category="WebApi")
	const FString& GetRequestParameter(const FString& Key) const;

	UFUNCTION(BlueprintCallable, Category="WebApi")
	void AddPreFilter(const TScriptInterface<IWebApiPreFilterInterface>& PreFilter);

	UFUNCTION(BlueprintCallable, Category="WebApi")
	void AddPostFilter(const TScriptInterface<IWebApiPostFilterInterface>& PostFilter);

	UFUNCTION(BlueprintNativeEvent, Category="WebApi")
	void OnPreProcessRequest();

	UFUNCTION(BlueprintCallable, Category="WebApi")
	bool ProcessRequest();

	UFUNCTION(BlueprintCallable, Category="WebApi")
	void CancelRequest();

	UFUNCTION(BlueprintPure, Category="WebApi")
	bool IsProcessingRequest() const;

private:
	// private function

	void OnRequestCompletedInternal(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccessed);
	void OnRequestProgressInternal(FHttpRequestPtr Request, int32 Sent, int32 Received);
};
