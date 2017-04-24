#pragma once

#include "CoreMinimal.h"
#include "WebApiRequestFilterInterface.h"
#include "WebApiResponseFilterInterface.h"
#include "WebApiConvToJsonFilter.generated.h"

/** JSON変換フィルター */
UCLASS(BlueprintType, Blueprintable)
class WEBAPI_API UWebApiConvToJsonFilter
	: public UObject
	, public IWebApiRequestFilterInterface
	, public IWebApiResponseFilterInterface
{
	GENERATED_BODY()

public:
	/**
	 * JSON変換フィルターを取得
	 * @return JSON変換フィルター
	 */
	UFUNCTION(BlueprintPure, Category="Online|WebApi")
	static UWebApiConvToJsonFilter* GetConvToJsonFilter();

	// UWebApiRequestFilterInterface interface
	virtual class UWebApiRequestBody* ExecuteRequestFilter_Implementation(class UWebApiRequestBody* Request) override;

	// UWebApiResponseFilterInterface interface
	virtual class UWebApiResponseBody* ExecuteResponseFilter_Implementation(class UWebApiResponseBody* Response) override;
};
