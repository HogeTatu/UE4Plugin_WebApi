#pragma once

#include "WebApiResponseBodyBase.generated.h"

UCLASS(ClassGroup=WebApi, Abstract, BlueprintType, Blueprintable)
class WEBAPI_API UWebApiResponseBodyBase : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	// public property

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Network|WebApi")
	int32 Code;

public:
	// public function

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, meta=(DisplayName="Create WebApi Response Body", BlueprintInternalUseOnly="true"), Category="Network|WebApi")
	static UWebApiResponseBodyBase* Create(TSubclassOf<class UWebApiResponseBodyBase> ClassType, const UWebApiResponseBodyBase* Source = nullptr);

	UFUNCTION(BlueprintCallable, Category="Network|WebApi", meta=(DisplayName = "CopyResponseBody"))
	virtual void Copy(const UWebApiResponseBodyBase* Source);
};
