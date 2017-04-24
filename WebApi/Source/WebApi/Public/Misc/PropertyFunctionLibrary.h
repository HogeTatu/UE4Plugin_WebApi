#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PropertyFunctionLibrary.generated.h"

/** プロパティ関連ライブラリ */
UCLASS()
class WEBAPI_API UPropertyFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:
	/**
	 * プロパティ一括コピー
	 * @param SourceObject コピー元オブジェクト
	 * @param DestObject コピー先オブジェクト
	 */
	UFUNCTION(BlueprintCallable, Category="NekoNeko|General")
	static void CopyAllObjectProperties(UObject* SourceObject, UObject* DestObject);

	/**
	 * プロパティコピー
	 * @param SourceObject コピー元オブジェクト
	 * @param DestObject コピー先オブジェクト
	 * @param PropertyNames プロパティ名リスト
	 */
	UFUNCTION(BlueprintCallable, Category="NekoNeko|General")
	static void CopyObjectProperties(UObject* SourceObject, UObject* DestObject, const TArray<FString>& PropertyNames);
};
