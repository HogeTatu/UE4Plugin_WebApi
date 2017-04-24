#pragma once

#include "CoreMinimal.h"
#include "WebApiResponseBody.h"
#include "WebApiResponseBodyString.generated.h"

UCLASS(BlueprintType, Blueprintable)
class WEBAPI_API UWebApiResponseBodyString : public UWebApiResponseBody
{
	GENERATED_UCLASS_BODY()

public:
	/** レスポンス文字列 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Online|WebApi")
	FString ResponseContent;
};
