#include "WebApiPrivatePCH.h"
#include "base64.h"
#include "urlencode.h"
#include "AuthFunctionLibrary.h"

UAuthFunctionLibrary::UAuthFunctionLibrary(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FString UAuthFunctionLibrary::GetTwitterAuthorizeUrl(const FString& RequestToken)
{
	return FString("https://api.twitter.com/oauth/authorize?oauth_token=") + RequestToken;
}

FString UAuthFunctionLibrary::Base64Encode(const TArray<uint8>& Source)
{
	return base64_encode(Source.GetData(), Source.Num()).c_str();
}

FString UAuthFunctionLibrary::UrlEncode(const FString& Source)
{
	FString SourceCopy = Source;
	return urlencode(TCHAR_TO_UTF8(*SourceCopy), URLEncode_Everything).c_str();
}
