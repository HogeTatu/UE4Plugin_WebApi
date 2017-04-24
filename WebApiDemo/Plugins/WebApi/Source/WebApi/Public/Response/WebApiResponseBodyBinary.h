#pragma once

#include "CoreMinimal.h"
#include "WebApiResponseBody.h"
#include "WebApiResponseBodyBinary.generated.h"

UCLASS(BlueprintType, Blueprintable)
class WEBAPI_API UWebApiResponseBodyBinary : public UWebApiResponseBody
{
	GENERATED_UCLASS_BODY()

public:
	/** レスポンスバイナリ */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Online|WebApi")
	TArray<uint8> ResponseContent;
};
