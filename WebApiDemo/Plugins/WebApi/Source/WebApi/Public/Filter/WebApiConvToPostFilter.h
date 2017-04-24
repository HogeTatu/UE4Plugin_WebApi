#pragma once

#include "CoreMinimal.h"
#include "WebApiRequestFilterInterface.h"
#include "WebApiResponseFilterInterface.h"
#include "WebApiConvToPostFilter.generated.h"

/** POST変換フィルター */
UCLASS(BlueprintType, Blueprintable)
class WEBAPI_API UWebApiConvToPostFilter
	: public UObject
	, public IWebApiRequestFilterInterface
{
	GENERATED_BODY()

public:
	/**
	 * POST変換フィルターを取得
	 * @return POST変換フィルター
	 */
	UFUNCTION(BlueprintPure, Category="Online|WebApi")
	static UWebApiConvToPostFilter* GetConvToPostFilter();

	// UWebApiRequestFilterInterface interface
	virtual class UWebApiRequestBody* ExecuteRequestFilter_Implementation(class UWebApiRequestBody* Request) override;
};
