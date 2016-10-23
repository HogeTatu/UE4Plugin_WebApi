#include "WebApiPrivatePCH.h"
#include "ImageUtils.h"
#include "ScreenshotCapture.h"

UScreenshotCapture::UScreenshotCapture(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UScreenshotCapture::ProcessRequestCapture()
{
	ReceivedScreenshotCaptureDelegateHandle = UGameViewportClient::OnScreenshotCaptured().AddUObject(this, &UScreenshotCapture::OnScreenshotCapturedInternal);

	FScreenshotRequest::RequestScreenshot( FString(), true, true );
}

void UScreenshotCapture::BeginDestroy()
{
	RemoveScreenshotCaptureDelegate();

	Super::BeginDestroy();
}

void UScreenshotCapture::RemoveScreenshotCaptureDelegate()
{
	if (ReceivedScreenshotCaptureDelegateHandle.IsValid())
	{
		UGameViewportClient::OnScreenshotCaptured().Remove(ReceivedScreenshotCaptureDelegateHandle);
	}
}

void UScreenshotCapture::OnScreenshotCapturedInternal(int32 Width, int32 Height, const TArray<FColor>& Bitmap)
{
	TArray<uint8> Data;
	TArray<FColor> BitmapCopy(Bitmap);
	FImageUtils::CompressImageArray(Width, Height, BitmapCopy, Data);

	ReceivedScreenshotCaptureDelegate.Broadcast(Data, Width, Height);

	RemoveScreenshotCaptureDelegate();
}
