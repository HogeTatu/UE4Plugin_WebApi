#pragma once

#include "WebApiResponseBodyString.h"
#include "WebApiResponseBodyToken.generated.h"

UCLASS(ClassGroup=WebApi, BlueprintType, Blueprintable)
class WEBAPI_API UWebApiResponseBodyToken : public UWebApiResponseBodyString
{
	GENERATED_UCLASS_BODY()

private:
	// private variable

	FString Token;
	FString TokenSecret;

public:
	// public function

	virtual void SetResponse(const FString& Response) override;

	UFUNCTION(BlueprintPure, Category="Network|WebApi")
	FString GetToken() const
	{
		return Token;
	}

	UFUNCTION(BlueprintPure, Category="Network|WebApi")
	FString GetTokenSecret() const
	{
		return TokenSecret;
	}
};
