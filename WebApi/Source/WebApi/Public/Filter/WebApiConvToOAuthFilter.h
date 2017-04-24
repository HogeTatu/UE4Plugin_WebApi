#pragma once

#include "CoreMinimal.h"
#include "WebApiRequestFilterInterface.h"
#include "WebApiResponseFilterInterface.h"
#include "WebApiConvToOAuthFilter.generated.h"

/** OAuth変換フィルター */
UCLASS(BlueprintType, Blueprintable)
class WEBAPI_API UWebApiConvToOAuthFilter
	: public UObject
	, public IWebApiRequestFilterInterface
	, public IWebApiResponseFilterInterface
{
	GENERATED_BODY()

public:
	/**
	 * OAuth変換フィルターを取得
	 * @return OAuth変換フィルター
	 */
	UFUNCTION(BlueprintPure, Category="Online|WebApi")
	static UWebApiConvToOAuthFilter* GetConvToOAuthFilter();

	// UWebApiRequestFilterInterface interface
	virtual class UWebApiRequestBody* ExecuteRequestFilter_Implementation(class UWebApiRequestBody* Request) override;

	// UWebApiResponseFilterInterface interface
	virtual class UWebApiResponseBody* ExecuteResponseFilter_Implementation(class UWebApiResponseBody* Response) override;
};
