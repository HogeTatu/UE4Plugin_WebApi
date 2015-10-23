#include "WebApiPrivatePCH.h"
#include "WebApiRequestBodyUrlParameter.h"

#define LOG_CATEGORY LogTemp

static FString Equal = TEXT("=");
static FString Delimiter = TEXT("&");

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
	FString UrlParameter;
	int32 Count = 0;
	int32 CountMax = Parameters.Num();

	for (const auto& Entry : Parameters)
	{
		UrlParameter += Entry.Key;
		UrlParameter += Equal;
		UrlParameter += Entry.Value;

		if(++Count < CountMax)
		{
			UrlParameter += Delimiter;
		}
	}

	Body = UrlParameter;
	return true;
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
