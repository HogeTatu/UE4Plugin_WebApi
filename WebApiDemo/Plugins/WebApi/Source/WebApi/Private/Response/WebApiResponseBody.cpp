#include "WebApiResponseBody.h"
#include "UObject/Package.h"

TArray<FString> UWebApiResponseBody::CachedUObjectPropertyNames;

UWebApiResponseBody::UWebApiResponseBody(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, ResponseCode(0)
{
}

UWebApiResponseBody* UWebApiResponseBody::Create(TSubclassOf<UWebApiResponseBody> ResponseClass)
{
	UObject* Outer = GetTransientPackage();
	return NewObject<UWebApiResponseBody>(Outer, ResponseClass);
}

TArray<FString> UWebApiResponseBody::GetPropertyNames(TSubclassOf<UWebApiResponseBody> ResponseClass)
{
	if (CachedUObjectPropertyNames.Num() <= 0)
	{
		for (auto Property : TFieldRange<const UProperty>(UObject::StaticClass()))
		{
			CachedUObjectPropertyNames.Add(Property->GetName());
		}
	}

	TArray<FString> PropertyNames;
	for (auto Property : TFieldRange<const UProperty>(ResponseClass))
	{
		int32 Index = CachedUObjectPropertyNames.Find(Property->GetName());
		if (Index == INDEX_NONE)
		{
			PropertyNames.Add(Property->GetName());
		}
	}
	return PropertyNames;
}
