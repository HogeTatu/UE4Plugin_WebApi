#include "WebApiPrivatePCH.h"
#include "JsonAccessor.h"

UJsonAccessor::UJsonAccessor()
{
}

UJsonAccessor::UJsonAccessor(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UJsonAccessor* UJsonAccessor::Create(const FString& FieldName, const TSharedPtr<FJsonObject>& JsonObject)
{
	auto Instance = NewObject<UJsonAccessor>(GetTransientPackage(), UJsonAccessor::StaticClass());
	Instance->FieldName = FieldName;
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

bool UJsonAccessor::TryGetIntField(const FString& FieldName, int32& Out) const
{
	check(JsonObject.IsValid());
	return JsonObject->TryGetNumberField(FieldName, Out);
}

bool UJsonAccessor::TryGetIntArrayField(const FString& FieldName, TArray<int32>& Out) const
{
	const TArray<TSharedPtr<FJsonValue>>* OutArray;
	if(JsonObject->TryGetArrayField(FieldName, OutArray) == false)
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
			UE_LOG(LogTemp, Warning, TEXT("%s array's item is not int32."), *FieldName);
		}
	}
	return true;
}

bool UJsonAccessor::TryGetFloatField(const FString& FieldName, float& Out) const
{
	double OutDouble;
	if(JsonObject->TryGetNumberField(FieldName, OutDouble) == false)
	{
		return false;
	}

	Out = (float)OutDouble;
	return true;
}

bool UJsonAccessor::TryGetFloatArrayField(const FString& FieldName, TArray<float>& Out) const
{
	const TArray<TSharedPtr<FJsonValue>>* OutArray;
	if(JsonObject->TryGetArrayField(FieldName, OutArray) == false)
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
			UE_LOG(LogTemp, Warning, TEXT("%s array's item is not float."), *FieldName);
		}
	}
	return true;
}

bool UJsonAccessor::TryGetStringField(const FString& FieldName, FString& Out) const
{
	return JsonObject->TryGetStringField(FieldName, Out);
}

bool UJsonAccessor::TryGetStringArrayField(const FString& FieldName, TArray<FString>& Out) const
{
	return JsonObject->TryGetStringArrayField(FieldName, Out);
}

bool UJsonAccessor::TryGetBoolField(const FString& FieldName, bool& Out) const
{
	return JsonObject->TryGetBoolField(FieldName, Out);
}

bool UJsonAccessor::TryGetBoolArrayField(const FString& FieldName, TArray<bool>& Out) const
{
	const TArray<TSharedPtr<FJsonValue>>* OutArray;
	if(JsonObject->TryGetArrayField(FieldName, OutArray) == false)
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
			UE_LOG(LogTemp, Warning, TEXT("%s array's item is not boolean."), *FieldName);
		}
	}
	return true;
}

bool UJsonAccessor::TryGetObjectField(const FString& FieldName, UJsonAccessor*& Out) const
{
	const TSharedPtr<FJsonObject>* OutObject;
	if(JsonObject->TryGetObjectField(FieldName, OutObject) == false)
	{
		return false;
	}

	Out = Create(FieldName, *OutObject);
	return true;
}
