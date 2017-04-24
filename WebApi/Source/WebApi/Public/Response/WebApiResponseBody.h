#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "WebApiResponseBody.generated.h"

UCLASS(Abstract, BlueprintType, Blueprintable)
class WEBAPI_API UWebApiResponseBody : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	/** レスポンスコード */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Online|WebApi")
	int32 ResponseCode;

private:
	/** キャッシュしたUObjectプロパティ名リスト */
	static TArray<FString> CachedUObjectPropertyNames;

public:
	/**
	 * レスポンスインスタンスを作成
	 * @param ResponseClass レスポンスクラス
	 * @return レスポンスインスタンス
	 */
	UFUNCTION(BlueprintCallable, Category="Online|WebApi", meta=(DisplayName="Create Web Api Response", DeterminesOutputType="ResponseClass"))
	static UWebApiResponseBody* Create(TSubclassOf<UWebApiResponseBody> ResponseClass);

	/**
	 * レスポンスインスタンスを作成
	 * @return レスポンスインスタンス
	 */
	template <typename ResponseClassType>
	static ResponseClassType* Create()
	{
		return Cast<ResponseClassType>(Create(ResponseClassType::StaticClass()));
	}

	/**
	 * プロパティ名リストを作成
	 * @param ResponseClass レスポンスクラス
	 * @return プロパティ名リスト
	 */
	static TArray<FString> GetPropertyNames(TSubclassOf<UWebApiResponseBody> ResponseClass);
};
