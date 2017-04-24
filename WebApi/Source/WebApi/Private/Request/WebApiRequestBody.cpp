#include "WebApiRequestBody.h"
#include "UObject/Package.h"

TArray<FString> UWebApiRequestBody::CachedUObjectPropertyNames;

UWebApiRequestBody::UWebApiRequestBody(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, RequestHeaders()
	, IsDummyRequest(false)
{
}

UWebApiRequestBody* UWebApiRequestBody::Create(TSubclassOf<UWebApiRequestBody> RequestClass)
{
	UObject* Outer = GetTransientPackage();
	return NewObject<UWebApiRequestBody>(Outer, RequestClass);
}

TArray<FString> UWebApiRequestBody::GetPropertyNames(TSubclassOf<UWebApiRequestBody> RequestClass)
{
	if (CachedUObjectPropertyNames.Num() <= 0)
	{
		for (auto Property : TFieldRange<const UProperty>(UObject::StaticClass()))
		{
			CachedUObjectPropertyNames.Add(Property->GetName());
		}
	}

	TArray<FString> PropertyNames;
	for (auto Property : TFieldRange<const UProperty>(RequestClass))
	{
		int32 Index = CachedUObjectPropertyNames.Find(Property->GetName());
		if (Index == INDEX_NONE)
		{
			PropertyNames.Add(Property->GetName());
		}
	}
	return PropertyNames;
}

void UWebApiRequestBody::SetRequestHeader(const FString& Key, const FString& Value)
{
	RequestHeaders.Add(Key, Value);
}

const FString& UWebApiRequestBody::GetRequestHeader(const FString& Key) const
{
	return RequestHeaders[Key];
}
