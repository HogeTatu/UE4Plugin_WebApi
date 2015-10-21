#pragma once

#include "WebApiResponseBodyString.h"
#include "JsonAccessor.h"
#include "WebApiResponseBodyJson.generated.h"

UCLASS(ClassGroup=WebApi, BlueprintType, Blueprintable)
class WEBAPI_API UWebApiResponseBodyJson : public UWebApiResponseBodyString
{
	GENERATED_UCLASS_BODY()

private:
	// private variable

	TSharedPtr<TJsonReader<>> JsonReader;
	UJsonAccessor* RootJsonAccessor;

public:
	// public function

	virtual void SetResponse(const FString& Response) override;

	UFUNCTION(BlueprintCallable, Category="WebApi")
	void GetRootJsonAccessor(UJsonAccessor*& RootJsonAccessor) const;
};
