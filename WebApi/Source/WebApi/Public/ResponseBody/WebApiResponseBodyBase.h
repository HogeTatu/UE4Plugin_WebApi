#pragma once

#include "WebApiResponseBodyBase.generated.h"

UCLASS(ClassGroup=WebApi, Abstract, BlueprintType, Blueprintable)
class WEBAPI_API UWebApiResponseBodyBase : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	// public property

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="WebApi")
	int32 Code;

public:
	// public function

	UFUNCTION(BlueprintCallable, Category = "WebApi")
	static UWebApiResponseBodyBase* CreateResponseBody(UClass* Class);

	UFUNCTION(BlueprintCallable, Category="WebApi", meta=(DisplayName = "CopyResponseBody"))
	virtual void Copy(const UWebApiResponseBodyBase* Source);
};
