#pragma once

#include "CoreMinimal.h"
#include "OnlineBlueprintCallProxyBase.h"
#include "ScreenshotCaptureCallProxy.generated.h"

/** スクリーンショットキャプチャープロキシ */
UCLASS(BlueprintType, Blueprintable)
class WEBAPI_API UScreenshotCaptureCallProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCaptureCompleted, int32, Width, int32, Height, const TArray<FColor>&, Bitmap);

public:
	/** スクリーンショットキャプチャー完了イベント */
	UPROPERTY(BlueprintAssignable)
	FOnCaptureCompleted OnCaptureCompleted;

private:
	/** ファイル名 */
	FString Filename;

	/** UI表示フラグ */
	bool bShowUI;

	/** ファイル名にサフィックスを付けるか */
	bool bAddFilenameSuffix;

public:
	/**
	 *　スクリーンショットキャプチャー実行
	 * @param Filename ファイル名
	 * @param bShowUI UI表示フラグ
	 * @param bAddFilenameSuffix ファイル名にサフィックスを付けるか
	 * @return スクリーンショットキャプチャー実行プロキシ
	 */
	UFUNCTION(BlueprintCallable, Category="Screenshot", meta=(BlueprintInternalUseOnly="true"))
	static UScreenshotCaptureCallProxy* RequestScreenshotCapture(const FString& Filename, bool bShowUI = true, bool bAddFilenameSuffix = true);

	/**
	 *　Bitmap画像データをPNG画像データに変換
	 * @param Width 画像幅
	 * @param Height 画像高さ
	 * @param Bitmap Bitmap画像データ
	 * @param Png PNG画像データ
	 * @return スクリーンショットキャプチャー実行プロキシ
	 */
	UFUNCTION(BlueprintCallable, Category="Screenshot")
	static void BitmapToPng(int32 Width, int32 Height, const TArray<FColor>& Bitmap, TArray<uint8>& Png);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;

private:
	/**
	 * スクリーンショットキャプチャー完了イベント
	 * @param Width 画像幅
	 * @param Height 画像高さ
	 * @param Bitmap Bitmap画像データ
	 */
	void OnCaptureCompletedInternal(int32 Width, int32 Height, const TArray<FColor>& Bitmap);
};
