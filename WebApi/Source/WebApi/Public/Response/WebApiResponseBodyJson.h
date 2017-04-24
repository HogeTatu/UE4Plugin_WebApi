#pragma once

#include "CoreMinimal.h"
#include "WebApiResponseBodyString.h"
#include "JsonAccessor.h"
#include "WebApiResponseBodyJson.generated.h"

UCLASS(BlueprintType, Blueprintable)
class WEBAPI_API UWebApiResponseBodyJson : public UWebApiResponseBodyString
{
	GENERATED_UCLASS_BODY()

public:
	/**
	 * JSONアクセッサンを取得
	 * @param JsonAccessor JSONアクセッサ
	 * @return 成功時にtrue
	 */
	bool GetJsonAccessor(FJsonAccessor& JsonAccessor);

	/**
	 * JSONアクセッサンを取得
	 * @param JsonAccessor JSONアクセッサ
	 * @param Success 成功時にtrue
	 */
	UFUNCTION(BlueprintCallable, Category="Online|WebApi")
	void GetJsonAccessor(FJsonAccessor& JsonAccessor, bool& Success)
	{
		Success = GetJsonAccessor(JsonAccessor);
	}
};
