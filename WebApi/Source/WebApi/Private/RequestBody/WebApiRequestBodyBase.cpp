#include "WebApiPrivatePCH.h"
#include "WebApiRequestBodyBase.h"

UWebApiRequestBodyBase::UWebApiRequestBodyBase(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UWebApiRequestBodyBase* UWebApiRequestBodyBase::CreateRequestBody(UClass* Class)
{
	return NewObject<UWebApiRequestBodyBase>(GetTransientPackage(), Class);
}

void UWebApiRequestBodyBase::Copy(const UWebApiRequestBodyBase* Source)
{
	Headers.Empty();
	for (const auto& Entry : Source->Headers)
	{
		Headers.Add(Entry.Key, Entry.Value);
	}
}

void UWebApiRequestBodyBase::SetHeader(const FString& Key, const FString& Value)
{
	Headers.Add(Key, Value);
}

const FString& UWebApiRequestBodyBase::GetHeader(const FString& Key) const
{
	return Headers[Key];
}

const TMap<FString, FString>& UWebApiRequestBodyBase::GetHeaders() const
{
	return Headers;
}
