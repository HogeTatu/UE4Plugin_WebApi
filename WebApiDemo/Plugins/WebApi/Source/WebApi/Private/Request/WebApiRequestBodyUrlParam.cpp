#include "WebApiRequestBodyUrlParam.h"

static FString Equal = TEXT("=");
static FString Delim = TEXT("&");

UWebApiRequestBodyUrlParam::UWebApiRequestBodyUrlParam(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, RequestParams()
{
}

bool UWebApiRequestBodyUrlParam::GetRequestBodyAsString(FString& RequestBody) const
{
	RequestBody = FString("");
	int32 Count = 0;
	int32 CountMax = RequestParams.Num();

	for (const auto& RequestParam : RequestParams)
	{
		RequestBody += urlencode(TCHAR_TO_UTF8(*RequestParam.Key), URLEncode_Everything).c_str();
		RequestBody += Equal;
		RequestBody += urlencode(TCHAR_TO_UTF8(*RequestParam.Value), URLEncode_Everything).c_str();

		if (++Count < CountMax)
		{
			RequestBody += Delim;
		}
	}

	return true;
}

void UWebApiRequestBodyUrlParam::SetRequestParam(const FString& Key, const FString& Value)
{
	RequestParams.Add(Key, Value);
}

const FString& UWebApiRequestBodyUrlParam::GetRequestParam(const FString& Key) const
{
	return RequestParams[Key];
}
