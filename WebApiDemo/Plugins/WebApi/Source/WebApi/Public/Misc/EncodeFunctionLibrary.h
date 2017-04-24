#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EncodeFunctionLibrary.generated.h"

/** エンコード関連ライブラリ */
UCLASS()
class WEBAPI_API UEncodeFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:
	/**
	 * Base64エンコード
	 * @param Source エンコード元
	 * @return エンコード結果
	 */
	UFUNCTION(BlueprintPure, Category="Online|Encode")
	static FString Base64Encode(const TArray<uint8>& Source);

	/**
	 * Base64デコード
	 * @param Source デコード元
	 * @return デコード結果
	 */
	UFUNCTION(BlueprintPure, Category="Online|Encode")
	static FString Base64Decode(const FString& Source);

	/**
	 * URLエンコード
	 * @param Source エンコード元
	 * @return エンコード結果
	 */
	UFUNCTION(BlueprintPure, Category="Online|Encode")
	static FString UrlEncode(const FString& Source);
};
