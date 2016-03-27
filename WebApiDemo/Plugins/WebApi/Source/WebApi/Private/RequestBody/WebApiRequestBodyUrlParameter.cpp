#include "WebApiPrivatePCH.h"
#include "urlencode.h"
#include "WebApiRequestBodyUrlParameter.h"

#define LOG_CATEGORY LogTemp

static FString Equal = TEXT("=");
static FString DefaultDelim = TEXT("&");

UWebApiRequestBodyUrlParameter::UWebApiRequestBodyUrlParameter(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UWebApiRequestBodyUrlParameter::Copy(const UWebApiRequestBodyBase* Source)
{
	UWebApiRequestBodyBase::Copy(Source);

	auto CastSource = Cast<const UWebApiRequestBodyUrlParameter>(Source);
	if(CastSource == nullptr) return;

	Parameters.Empty();
	for (const auto& Entry : CastSource->Parameters)
	{
		Parameters.Add(Entry.Key, Entry.Value);
	}
}

bool UWebApiRequestBodyUrlParameter::GetRequestBodyAsString(FString& Body) const
{
	return GetRequestBodyAsStringInternal(Body, DefaultDelim);
}

bool UWebApiRequestBodyUrlParameter::GetRequestBodyAsBytes(TArray<uint8>& Body) const
{
	UE_LOG(LOG_CATEGORY, Warning, TEXT("UWebApiRequestBodyUrlParameter::GetRequestBodyAsBytes is not supported."));
	return false;
}

void UWebApiRequestBodyUrlParameter::SetParameter(const FString& Key, const FString& Value)
{
	Parameters.Add(Key, Value);
}

const FString& UWebApiRequestBodyUrlParameter::GetParameter(const FString& Key) const
{
	return Parameters[Key];
}

const TMap<FString, FString>& UWebApiRequestBodyUrlParameter::GetParameters() const
{
	return Parameters;
}

int32 UWebApiRequestBodyUrlParameter::GetParameterCount() const
{
	return Parameters.Num();
}

bool UWebApiRequestBodyUrlParameter::GetRequestBodyAsStringInternal(FString& Body, const FString& Delim) const
{
	FString UrlParameter;
	int32 Count = 0;
	int32 CountMax = Parameters.Num();

	for (const auto& Entry : Parameters)
	{
		UrlParameter += urlencode(TCHAR_TO_UTF8(*Entry.Key), URLEncode_Everything).c_str();
		// UrlParameter += Entry.Key;
		UrlParameter += Equal;
		UrlParameter += urlencode(TCHAR_TO_UTF8(*Entry.Value), URLEncode_Everything).c_str();
		// UrlParameter += Entry.Value;

		if(++Count < CountMax)
		{
			UrlParameter += Delim;
		}
	}

	Body = UrlParameter;
	return true;
}
