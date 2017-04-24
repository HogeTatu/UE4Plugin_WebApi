#include "Misc/PropertyFunctionLibrary.h"

UPropertyFunctionLibrary::UPropertyFunctionLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UPropertyFunctionLibrary::CopyAllObjectProperties(UObject* SourceObject, UObject* DestObject)
{
	const UClass* SourceClass = SourceObject->GetClass();
	const UClass* DestClass = DestObject->GetClass();
	if (DestObject->IsA(SourceClass))
	{
		for (auto SourceProperty : TFieldRange<const UProperty>(SourceClass))
		{
			auto DestProperty = FindField<UProperty>(DestClass, *SourceProperty->GetNameCPP());
			if (!DestProperty)
			{
				continue;
			}

			const void* Source = SourceProperty->ContainerPtrToValuePtr<void>(SourceObject);
			void* Dest = DestProperty->ContainerPtrToValuePtr<void>(DestObject);
			SourceProperty->CopySingleValue(Dest, Source);
		}
	}
}

void UPropertyFunctionLibrary::CopyObjectProperties(UObject* SourceObject, UObject* DestObject, const TArray<FString>& PropertyNames)
{
	const UClass* SourceClass = SourceObject->GetClass();
	const UClass* DestClass = DestObject->GetClass();
	if (DestObject->IsA(SourceClass))
	{
		for (auto& PropertyName : PropertyNames)
		{
			auto SourceProperty = FindField<UProperty>(SourceClass, *PropertyName);
			if (!SourceProperty)
			{
				continue;
			}

			auto DestProperty = FindField<UProperty>(DestClass, *PropertyName);
			if (!DestProperty)
			{
				continue;
			}

			const void* Source = SourceProperty->ContainerPtrToValuePtr<void>(SourceObject);
			void* Dest = DestProperty->ContainerPtrToValuePtr<void>(DestObject);
			SourceProperty->CopySingleValue(Dest, Source);
		}
	}
}
