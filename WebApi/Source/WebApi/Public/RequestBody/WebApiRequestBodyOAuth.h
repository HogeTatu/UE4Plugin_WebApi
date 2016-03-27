#pragma once

#include "WebApiRequestBodyPost.h"
#include "WebApiRequestBodyOAuth.generated.h"

/**
 * Interface for the services manager.
 */
USTRUCT(BlueprintType)
struct WEBAPI_API FOAuthParameter
{
	GENERATED_USTRUCT_BODY()

	FOAuthParameter() {}
	virtual ~FOAuthParameter() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Network|WebApi|Auth")
	FString Url;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Network|WebApi|Auth")
	FString ConsumerKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Network|WebApi|Auth")
	FString ConsumerSecret;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Network|WebApi|Auth")
	FString Token;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Network|WebApi|Auth")
	FString TokenSecret;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Network|WebApi|Auth")
	FString Pin;
};

UCLASS(ClassGroup=WebApi, BlueprintType, Blueprintable)
class WEBAPI_API UWebApiRequestBodyOAuth : public UWebApiRequestBodyPost
{
	GENERATED_UCLASS_BODY()

public:
	// public function

	virtual bool GetRequestBodyAsString(FString& Body) const override;
	virtual bool GetRequestBodyAsBytes(TArray<uint8>& Body) const override;

	virtual void Copy(const UWebApiRequestBodyBase* Source) override;

	UFUNCTION(BlueprintCallable, Category="Network|WebApi|Auth")
	void SetAuthHeader(const FOAuthParameter& Param);
};
