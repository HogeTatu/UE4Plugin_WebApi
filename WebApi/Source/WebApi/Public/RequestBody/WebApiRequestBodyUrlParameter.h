#pragma once

#include "WebApiRequestBodyBase.h"
#include "WebApiRequestBodyUrlParameter.generated.h"

UCLASS(ClassGroup=WebApi, BlueprintType, Blueprintable)
class WEBAPI_API UWebApiRequestBodyUrlParameter : public UWebApiRequestBodyBase
{
	GENERATED_UCLASS_BODY()

protected:
	// protected variable

	TMap<FString, FString> Parameters;

public:
	// public function

	virtual EWebApiRequestType::Type GetRequestType() const override
	{
		return EWebApiRequestType::GET;
	}

	virtual EWebApiRequestParameterType::Type GetRequestParameterType() const override
	{
		return EWebApiRequestParameterType::STRING;
	}

	virtual bool GetRequestBodyAsString(FString& Body) const override;
	virtual bool GetRequestBodyAsBytes(TArray<uint8>& Body) const override;

	virtual void Copy(const UWebApiRequestBodyBase* Source) override;

	UFUNCTION(BlueprintCallable, Category="Network|WebApi")
	void SetParameter(const FString& Key, const FString& Value);

	UFUNCTION(BlueprintPure, Category="Network|WebApi")
	const FString& GetParameter(const FString& Key) const;

	const TMap<FString, FString>& GetParameters() const;

	UFUNCTION(BlueprintPure, Category="Network|WebApi")
	int32 GetParameterCount() const;

protected:
	// protected function

	bool GetRequestBodyAsStringInternal(FString& Body, const FString& Delim) const;
};
