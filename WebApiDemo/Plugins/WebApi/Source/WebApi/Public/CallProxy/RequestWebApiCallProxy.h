#pragma once

#include "CoreMinimal.h"
#include "OnlineBlueprintCallProxyBase.h"
#include "RequestWebApiCallProxy.generated.h"

/** 開始コールバックパラメータ */
USTRUCT(BlueprintType)
struct WEBAPI_API FRequestWebApiStartParam
{
	GENERATED_USTRUCT_BODY()

public:
	FRequestWebApiStartParam()
		: Request(nullptr)
	{}

	FRequestWebApiStartParam(class UWebApiRequestBody* InRequest)
		: Request(InRequest)
	{}

	/** リクエスト */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Online|WebApi")
	class UWebApiRequestBody* Request;
};

/** 経過コールバックパラメータ */
USTRUCT(BlueprintType)
struct WEBAPI_API FRequestWebApiProgressParam
{
	GENERATED_USTRUCT_BODY()

public:
	FRequestWebApiProgressParam()
		: SentBytes(0)
		, ReceivedBytes(0)
	{}

	FRequestWebApiProgressParam(int32 InSentBytes, int32 InReceivedBytes)
		: SentBytes(InSentBytes)
		, ReceivedBytes(InReceivedBytes)
	{}

	/** 送信済みバイト数 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Online|WebApi")
	int32 SentBytes;

	/** 受信済みバイト数 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Online|WebApi")
	int32 ReceivedBytes;
};

/** 結果コールバックパラメータ */
USTRUCT(BlueprintType)
struct WEBAPI_API FRequestWebApiResultParam
{
	GENERATED_USTRUCT_BODY()

public:
	FRequestWebApiResultParam()
		: Response(nullptr)
	{}

	FRequestWebApiResultParam(class UWebApiResponseBody* InResponse)
		: Response(InResponse)
	{}

	/** リクエスト */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Online|WebApi")
	class UWebApiResponseBody* Response;
};

/** リクエストコールバックパラメータ */
UCLASS(BlueprintType, Blueprintable)
class WEBAPI_API URequestWebApiCallbackParam : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	/** 開始コールバックパラメータ（OnStart用） */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Online|WebApi")
	FRequestWebApiStartParam StartParam;

	/** 経過コールバックパラメータ（OnProgress用） */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Online|WebApi")
	FRequestWebApiProgressParam ProgressParam;

	/** 結果コールバックパラメータ（OnSuccess、OnFailure、OnCompleted用） */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Online|WebApi")
	FRequestWebApiResultParam ResultParam;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRequestWebApiCallbackParamDelegate, class UWebApi*, WebApi, URequestWebApiCallbackParam*, Param);

/** WebApiリクエスト実行プロキシ */
UCLASS(BlueprintType, Blueprintable)
class WEBAPI_API URequestWebApiCallProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

public:
	/** 開始コールバック */
	UPROPERTY(BlueprintAssignable)
	FRequestWebApiCallbackParamDelegate OnStart;

	/** 経過コールバック */
	UPROPERTY(BlueprintAssignable)
	FRequestWebApiCallbackParamDelegate OnProgress;

	/** 成功コールバック */
	UPROPERTY(BlueprintAssignable)
	FRequestWebApiCallbackParamDelegate OnSuccess;

	/** 失敗コールバック */
	UPROPERTY(BlueprintAssignable)
	FRequestWebApiCallbackParamDelegate OnFailure;

	/** 完了コールバック */
	UPROPERTY(BlueprintAssignable)
	FRequestWebApiCallbackParamDelegate OnCompleted;

private:
	/** コールバックパラメータ */
	UPROPERTY(Transient)
	URequestWebApiCallbackParam* CallbackParam;

	/** API */
	class UWebApi* WebApi;

	/** リクエスト */
	class UWebApiRequestBody* Request;

public:
	/**
	 *　WebApiリクエスト実行
	 * @param WebApi API
	 * @param Request リクエスト本体
	 * @return WebApiリクエスト実行プロキシ
	 */
	UFUNCTION(BlueprintCallable, Category="Online|WebApi", meta=(BlueprintInternalUseOnly="true"))
	static URequestWebApiCallProxy* RequestWebApi(class UWebApi* WebApi, class UWebApiRequestBody* Request);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;

private:
	/**
	 * コールバックバインド
	 * @param Api API
	 * @param Request リクエスト
	 */
	template <typename DelegateType>
	void BindCallback(DelegateType& Delegate, const FName& FuncName)
	{
		FScriptDelegate ScriptDelegate;
		ScriptDelegate.BindUFunction(this, FuncName);
		Delegate.Add(ScriptDelegate);
	};

	/**
	 * 開始コールバック
	 * @param Api API
	 * @param Request リクエスト
	 */
	UFUNCTION()
	void OnRequestStartInternal(class UWebApi* Api, class UWebApiRequestBody* Request);

	/**
	 * 経過コールバック
	 * @param Api API
	 * @param SentBytes 送信済みパケット数
	 * @param ReceivedBytes 受信済みパケット数
	 */
	UFUNCTION()
	void OnRequestProgressInternal(class UWebApi* Api, int32 SentBytes, int32 ReceivedBytes);

	/**
	 * 成功コールバック
	 * @param Api API
	 * @param Response レスポンス
	 */
	UFUNCTION()
	void OnRequestSuccessInternal(class UWebApi* Api, class UWebApiResponseBody* Response);

	/**
	 * 失敗コールバック
	 * @param Api API
	 * @param Response レスポンス
	 */
	UFUNCTION()
	void OnRequestFailureInternal(class UWebApi* Api, class UWebApiResponseBody* Response);

	/**
	 * 完了コールバック
	 * @param Api API
	 * @param Response レスポンス
	 */
	UFUNCTION()
	void OnRequestCompletedInternal(class UWebApi* Api, class UWebApiResponseBody* Response);
};
