#pragma once

#include "CoreMinimal.h"
#include "WebApiRequestFilterInterface.h"
#include "WebApiDummyRequestFilter.generated.h"

/** ダミーリクエストフィルター */
UCLASS(BlueprintType, Blueprintable)
class WEBAPI_API UWebApiDummyRequestFilter
	: public UObject
	, public IWebApiRequestFilterInterface
{
	GENERATED_BODY()

public:
	/**
	 * ダミーリクエストフィルターを取得
	 * @return ダミーリクエストフィルター
	 */
	UFUNCTION(BlueprintPure, Category="Online|WebApi")
	static UWebApiDummyRequestFilter* GetDummyRequestFilter();

	// UWebApiRequestFilterInterface interface
	virtual class UWebApiRequestBody* ExecuteRequestFilter_Implementation(class UWebApiRequestBody* Request) override;
};
