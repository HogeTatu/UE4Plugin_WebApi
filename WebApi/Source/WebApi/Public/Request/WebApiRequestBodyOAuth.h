#pragma once

#include "CoreMinimal.h"
#include "WebApiRequestBodyPost.h"
#include "WebApiRequestBodyOAuth.generated.h"

/** OAuthパラメータ */
USTRUCT(BlueprintType)
struct WEBAPI_API FOAuthParam
{
	GENERATED_BODY()

	/** URL */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Online|WebApi")
	FString Url;

	/** Consumer Key */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Online|WebApi")
	FString ConsumerKey;

	/** Consumer Secret */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Online|WebApi")
	FString ConsumerSecret;

	/** Token */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Online|WebApi")
	FString Token;

	/** Token Secret */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Online|WebApi")
	FString TokenSecret;

	/** PINコード */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Online|WebApi")
	FString Pin;
};

/** OAuthリクエスト */
UCLASS(BlueprintType, Blueprintable)
class WEBAPI_API UWebApiRequestBodyOAuth : public UWebApiRequestBodyPost
{
	GENERATED_UCLASS_BODY()

public:
	/**
	 * OAuthパラメータをリクエストヘッダーに設定
	 * @param Param OAuthパラメータ
	 */
	UFUNCTION(BlueprintCallable, Category="Online|WebApi")
	void SetAuthHeader(const FOAuthParam& Param);
};
