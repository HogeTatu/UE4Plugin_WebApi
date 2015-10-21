#pragma once

#include "WebApiRequestBodyUrlParameter.h"
#include "WebApiRequestBodyPost.generated.h"

UCLASS(ClassGroup=WebApi, BlueprintType, Blueprintable)
class WEBAPI_API UWebApiRequestBodyPost : public UWebApiRequestBodyUrlParameter
{
	GENERATED_UCLASS_BODY()

public:
	// public function

	virtual EWebApiRequestType::Type GetRequestType() const override
	{
		return EWebApiRequestType::POST;
	}

	virtual EWebApiRequestParameterType::Type GetRequestParameterType() const override
	{
		return EWebApiRequestParameterType::STRING;
	}

	virtual bool GetRequestBodyAsString(FString& Body) const override;
	virtual bool GetRequestBodyAsBytes(TArray<uint8>& Body) const override;

	virtual void Copy(const UWebApiRequestBodyBase* Source) override;

private:
	// private function

	virtual void SetDefaultHeaders();
};
