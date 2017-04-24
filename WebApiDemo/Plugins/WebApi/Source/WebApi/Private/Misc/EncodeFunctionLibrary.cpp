#include "EncodeFunctionLibrary.h"
#include "base64.h"
#include "urlencode.h"

UEncodeFunctionLibrary::UEncodeFunctionLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FString UEncodeFunctionLibrary::Base64Encode(const TArray<uint8>& Source)
{
	return base64_encode(Source.GetData(), Source.Num()).c_str();
}

FString UEncodeFunctionLibrary::Base64Decode(const FString& Source)
{
	return base64_decode(TCHAR_TO_UTF8(*Source)).c_str();
}

FString UEncodeFunctionLibrary::UrlEncode(const FString& Source)
{
	return urlencode(TCHAR_TO_UTF8(*Source), URLEncode_Everything).c_str();
}
