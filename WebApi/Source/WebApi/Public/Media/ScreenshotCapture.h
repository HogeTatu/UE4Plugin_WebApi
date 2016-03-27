#pragma once

#include "ScreenshotCapture.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnReceivedScreenshotCapture, const TArray<uint8>&, Data, int32, Width, int32, Height);

UCLASS(ClassGroup=Screenshot, BlueprintType, Blueprintable)
class WEBAPI_API UScreenshotCapture : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	// public property

	UPROPERTY(BlueprintAssignable, Category="Media|Screenshot")
	FOnReceivedScreenshotCapture ReceivedScreenshotCaptureDelegate;

public:
	// public function

	UFUNCTION(BlueprintCallable, Category="Media|Screenshot")
	void ProcessRequestCapture();

protected:
	// protected function

	virtual void BeginDestroy() override;

private:
	// private function

	void RemoveScreenshotCaptureDelegate();

	void OnScreenshotCapturedInternal(int32 Width, int32 Height, const TArray<FColor>& Bitmap);

private:
	// private property

	FDelegateHandle ReceivedScreenshotCaptureDelegateHandle;
};
