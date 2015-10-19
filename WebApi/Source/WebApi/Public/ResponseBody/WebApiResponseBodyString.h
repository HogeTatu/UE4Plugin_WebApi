#pragma once

#include "WebApiResponseBodyBase.h"
#include "WebApiResponseBodyString.generated.h"

UCLASS(ClassGroup=WebApi, BlueprintType, Blueprintable)
class WEBAPI_API UWebApiResponseBodyString : public UWebApiResponseBodyBase
{
	GENERATED_UCLASS_BODY()

protected:
	// protected variable

	FString Response;

public:
	// public function

	virtual void Copy(const UWebApiResponseBodyBase* Source) override;

	UFUNCTION(BlueprintCallable, Category="WebApi")
	virtual void SetResponse(const FString& Response);

	UFUNCTION(BlueprintPure, Category="WebApi")
	virtual const FString& GetResponse() const;
};
