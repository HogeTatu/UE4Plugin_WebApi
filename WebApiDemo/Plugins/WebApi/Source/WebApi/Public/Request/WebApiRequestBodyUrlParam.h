#pragma once

#include "CoreMinimal.h"
#include "WebApiRequestBody.h"
#include "WebApiRequestBodyUrlParam.generated.h"

UCLASS(BlueprintType, Blueprintable)
class WEBAPI_API UWebApiRequestBodyUrlParam : public UWebApiRequestBody
{
	GENERATED_UCLASS_BODY()

public:
	/** リクエストパラメータ */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Online|WebApi")
	TMap<FString, FString> RequestParams;

public:
	// UWebApiRequestBody interface
	virtual EWebApiRequestType GetRequestType() const override { return EWebApiRequestType::Get; }
	virtual bool GetRequestBodyAsString(FString& RequestBody) const override;

	/**
	 * リクエストパラメータ設定
	 * @param Key パラメータキー
	 * @param Value パラメータ値
	 */
	UFUNCTION(BlueprintCallable, Category="Online|WebApi")
	void SetRequestParam(const FString& Key, const FString& Value);

	/**
	 * リクエストパラメータ設定
	 * @param Key パラメータキー
	 * @param Value パラメータ値
	 */
	UFUNCTION(BlueprintCallable, Category="Online|WebApi")
	void SetNameRequestParam(const FString& Key, const FName& Value)
	{
		SetRequestParam(Key, Value.ToString());
	}

	/**
	 * リクエストパラメータ設定
	 * @param Key パラメータキー
	 * @param Value パラメータ値
	 */
	UFUNCTION(BlueprintCallable, Category="Online|WebApi")
	void SetTextRequestParam(const FString& Key, const FText& Value)
	{
		SetRequestParam(Key, Value.ToString());
	}

	/**
	 * リクエストパラメータ設定
	 * @param Key パラメータキー
	 * @param Value パラメータ値
	 */
	UFUNCTION(BlueprintCallable, Category="Online|WebApi")
	void SetIntegerRequestParam(const FString& Key, int32 Value)
	{
		SetRequestParam(Key, FString::FromInt(Value));
	}

	/**
	 * リクエストパラメータ設定
	 * @param Key パラメータキー
	 * @param Value パラメータ値
	 */
	UFUNCTION(BlueprintCallable, Category="Online|WebApi")
	void SetFloatRequestParam(const FString& Key, float Value)
	{
		SetRequestParam(Key, FString::SanitizeFloat(Value));
	}

	/**
	 * リクエストパラメータ取得
	 * @param Key パラメータキー
	 * @return パラメータ値
	 */
	UFUNCTION(BlueprintPure, Category="Online|WebApi")
	const FString& GetRequestParam(const FString& Key) const;

	/**
	 * リクエストパラメータ取得
	 * @param Key パラメータキー
	 * @return パラメータ値
	 */
	UFUNCTION(BlueprintPure, Category="Online|WebApi")
	int32 GetIntegerRequestParam(const FString& Key) const
	{
		return FCString::Atoi(*GetRequestParam(Key));
	}

	/**
	 * リクエストパラメータ取得
	 * @param Key パラメータキー
	 * @return パラメータ値
	 */
	UFUNCTION(BlueprintPure, Category="Online|WebApi")
	float GetFloatRequestParam(const FString& Key) const
	{
		return FCString::Atof(*GetRequestParam(Key));
	}
};
