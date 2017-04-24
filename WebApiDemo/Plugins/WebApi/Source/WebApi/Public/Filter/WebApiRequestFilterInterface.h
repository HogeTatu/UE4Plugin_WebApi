#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WebApiRequestFilterInterface.generated.h"

/** リクエスト時フィルターインターフェース */
UINTERFACE()
class WEBAPI_API UWebApiRequestFilterInterface : public UInterface
{
	GENERATED_BODY()
};

/** リクエスト時フィルターインターフェース */
class WEBAPI_API IWebApiRequestFilterInterface
{
	GENERATED_BODY()

public:
	/**
	 * リクエスト時フィルタリング実行
	 * @param Request リクエスト
	 * @return フィルタリング実行後リクエスト
	 */
	UFUNCTION(BlueprintNativeEvent, Category="Online|WebApi")
	class UWebApiRequestBody* ExecuteRequestFilter(class UWebApiRequestBody* Request);
};
