#pragma once

#include "Http.h"
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

	virtual void PostInitProperties() override;

protected:
	// protected variable

	UPROPERTY(Transient)
	UWebApiRequestBodyUrlParameter* RequestBodyOrg;

	TQueue<UObject*> PreFilters;
	TQueue<UObject*> PostFilters;
	FHttpRequestPtr ProcessingRequest;

private:
	// private variable

	bool bProcessing;

public:
	// public property

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Network|WebApi")
	FString Domain;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Network|WebApi")
	FString Path;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Network|WebApi")
	TArray<int32> SuccessResponseCodes;

	UPROPERTY(BlueprintAssignable, Category="Network|WebApi")
	FOnWebApiRequestStartDelegate OnRequestStart;

	UPROPERTY(BlueprintAssignable, Category="Network|WebApi")
	FOnWebApiRequestProgressDelegate OnRequestProgress;

	UPROPERTY(BlueprintAssignable, Category="Network|WebApi")
	FOnWebApiRequestSuccessedDelegate OnRequestSuccessed;

	UPROPERTY(BlueprintAssignable, Category="Network|WebApi")
	FOnWebApiRequestFailedDelegate OnRequestFailed;

	UPROPERTY(BlueprintAssignable, Category="Network|WebApi")
	FOnWebApiRequestCompletedDelegate OnRequestCompleted;

public:
	// public function

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, meta=(DisplayName="Create WebApi", BlueprintInternalUseOnly="true"), Category="Network|WebApi")
	static UWebApi* Create(TSubclassOf<class UWebApi> ClassType);

	UFUNCTION(BlueprintPure, Category="Network|WebApi")
	FString GetRequestURL() const;

	UFUNCTION(BlueprintCallable, Category="Network|WebApi")
	void SetRequestParameter(const FString& Key, const FString& Value);

	UFUNCTION(BlueprintCallable, Category="Network|WebApi")
	const FString& GetRequestParameter(const FString& Key) const;

	UFUNCTION(BlueprintCallable, Category="Network|WebApi")
	void AddPreFilter(const TScriptInterface<IWebApiPreFilterInterface>& PreFilter);

	UFUNCTION(BlueprintCallable, Category="Network|WebApi")
	void AddPostFilter(const TScriptInterface<IWebApiPostFilterInterface>& PostFilter);

	UFUNCTION(BlueprintNativeEvent, Category="Network|WebApi")
	void OnPreProcessRequest();

	UFUNCTION(BlueprintCallable, Category="Network|WebApi")
	bool ProcessRequest();

	UFUNCTION(BlueprintCallable, Category="Network|WebApi")
	void CancelRequest();

	UFUNCTION(BlueprintPure, Category="Network|WebApi")
	bool IsProcessingRequest() const;

private:
	// private function

	void OnRequestCompletedInternal(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccessed);
	void OnRequestProgressInternal(FHttpRequestPtr Request, int32 Sent, int32 Received);
};
