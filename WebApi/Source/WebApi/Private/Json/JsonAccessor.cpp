#include "WebApiPrivatePCH.h"
#include "JsonAccessor.h"

UJsonAccessor::UJsonAccessor()
{
}

UJsonAccessor::UJsonAccessor(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UJsonAccessor* UJsonAccessor::Create(const FString& InFieldName, const TSharedPtr<FJsonObject>& JsonObject)
{
	auto Instance = NewObject<UJsonAccessor>(GetTransientPackage(), UJsonAccessor::StaticClass());
	Instance->FieldName = InFieldName;
	Instance->JsonObject = JsonObject;
	return Instance;
}

const FString& UJsonAccessor::GetFieldName() const
{
	return FieldName;
}

const TSharedPtr<FJsonObject>& UJsonAccessor::GetJsonObject() const
{
	return JsonObject;
}

bool UJsonAccessor::TryGetIntField(const FString& InFieldName, int32& Out) const
{
	check(JsonObject.IsValid());
	return JsonObject->TryGetNumberField(InFieldName, Out);
}

bool UJsonAccessor::TryGetIntArrayField(const FString& InFieldName, TArray<int32>& Out) const
{
	const TArray<TSharedPtr<FJsonValue>>* OutArray;
	if(JsonObject->TryGetArrayField(InFieldName, OutArray) == false)
	{
		return false;
	}

	for (const auto& JsonValue : *OutArray)
	{
		int32 Int;
		if(JsonValue->TryGetNumber(Int))
		{
			Out.Add(Int);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%s array's item is not int32."), *InFieldName);
		}
	}
	return true;
}

bool UJsonAccessor::TryGetFloatField(const FString& InFieldName, float& Out) const
{
	double OutDouble;
	if(JsonObject->TryGetNumberField(InFieldName, OutDouble) == false)
	{
		return false;
	}

	Out = (float)OutDouble;
	return true;
}

bool UJsonAccessor::TryGetFloatArrayField(const FString& InFieldName, TArray<float>& Out) const
{
	const TArray<TSharedPtr<FJsonValue>>* OutArray;
	if(JsonObject->TryGetArrayField(InFieldName, OutArray) == false)
	{
		return false;
	}

	for (const auto& JsonValue : *OutArray)
	{
		double Double;
		if(JsonValue->TryGetNumber(Double))
		{
			Out.Add((float)Double);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%s array's item is not float."), *InFieldName);
		}
	}
	return true;
}

bool UJsonAccessor::TryGetStringField(const FString& InFieldName, FString& Out) const
{
	return JsonObject->TryGetStringField(InFieldName, Out);
}

bool UJsonAccessor::TryGetStringArrayField(const FString& InFieldName, TArray<FString>& Out) const
{
	return JsonObject->TryGetStringArrayField(InFieldName, Out);
}

bool UJsonAccessor::TryGetBoolField(const FString& InFieldName, bool& Out) const
{
	return JsonObject->TryGetBoolField(InFieldName, Out);
}

bool UJsonAccessor::TryGetBoolArrayField(const FString& InFieldName, TArray<bool>& Out) const
{
	const TArray<TSharedPtr<FJsonValue>>* OutArray;
	if(JsonObject->TryGetArrayField(InFieldName, OutArray) == false)
	{
		return false;
	}

	for (const auto& JsonValue : *OutArray)
	{
		bool Bool;
		if(JsonValue->TryGetBool(Bool))
		{
			Out.Add(Bool);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%s array's item is not boolean."), *InFieldName);
		}
	}
	return true;
}

bool UJsonAccessor::TryGetObjectField(const FString& InFieldName, UJsonAccessor*& Out) const
{
	const TSharedPtr<FJsonObject>* OutObject;
	if(JsonObject->TryGetObjectField(InFieldName, OutObject) == false)
	{
		return false;
	}

	Out = Create(InFieldName, *OutObject);
	return true;
}
