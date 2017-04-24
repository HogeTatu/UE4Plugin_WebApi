#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WebApiResponseFilterInterface.generated.h"

/** レスポンス時フィルターインターフェース */
UINTERFACE()
class WEBAPI_API UWebApiResponseFilterInterface : public UInterface
{
	GENERATED_BODY()
};

/** レスポンス時フィルターインターフェース */
class WEBAPI_API IWebApiResponseFilterInterface
{
	GENERATED_BODY()

public:
	/**
	 * レスポンス時フィルタリング実行
	 * @param Response レスポンス
	 * @return フィルタリング実行後レスポンス
	 */
	UFUNCTION(BlueprintNativeEvent, Category="Online|WebApi")
	class UWebApiResponseBody* ExecuteResponseFilter(class UWebApiResponseBody* Response);
};
