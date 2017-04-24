#include "ScreenshotCaptureCallProxy.h"
#include "ImageUtils.h"
#include "Engine/GameViewportClient.h"
#include "UnrealClient.h"

UScreenshotCaptureCallProxy::UScreenshotCaptureCallProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, Filename()
	, bShowUI(false)
	, bAddFilenameSuffix(false)
{
}

UScreenshotCaptureCallProxy* UScreenshotCaptureCallProxy::RequestScreenshotCapture(const FString& InFilename, bool bInShowUI, bool bInAddFilenameSuffix)
{
	UScreenshotCaptureCallProxy* Proxy = NewObject<UScreenshotCaptureCallProxy>();
	Proxy->Filename = InFilename;
	Proxy->bShowUI = bInShowUI;
	Proxy->bAddFilenameSuffix = bInAddFilenameSuffix;
	return Proxy;
}

void UScreenshotCaptureCallProxy::BitmapToPng(int32 Width, int32 Height, const TArray<FColor>& Bitmap, TArray<uint8>& Png)
{
	FImageUtils::CompressImageArray(Width, Height, Bitmap, Png);
}

void UScreenshotCaptureCallProxy::Activate()
{
	UGameViewportClient::OnScreenshotCaptured().AddUObject(this, &UScreenshotCaptureCallProxy::OnCaptureCompletedInternal);
	FScreenshotRequest::RequestScreenshot(Filename, bShowUI, bAddFilenameSuffix);
}

void UScreenshotCaptureCallProxy::OnCaptureCompletedInternal(int32 Width, int32 Height, const TArray<FColor>& Bitmap)
{
	OnCaptureCompleted.Broadcast(Width, Height, Bitmap);
}
