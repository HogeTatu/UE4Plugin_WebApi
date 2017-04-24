#include "JsonFunctionLibrary.h"
#include "WebApiLog.h"

UJsonFunctionLibrary::UJsonFunctionLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UJsonFunctionLibrary::TryGetIntField(const FJsonAccessor& JsonAccessor, const FString& InFieldName, int32& Out)
{
	return JsonAccessor.JsonObject->TryGetNumberField(InFieldName, Out);
}

bool UJsonFunctionLibrary::TryGetIntArrayField(const FJsonAccessor& JsonAccessor, const FString& InFieldName, TArray<int32>& Out)
{
	const TArray<TSharedPtr<FJsonValue>>* OutArray;
	if(JsonAccessor.JsonObject->TryGetArrayField(InFieldName, OutArray) == false)
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
			UE_LOG(LogWebApi, Warning, TEXT("%s array's item is not int32."), *InFieldName);
		}
	}
	return true;
}

bool UJsonFunctionLibrary::TryGetFloatField(const FJsonAccessor& JsonAccessor, const FString& InFieldName, float& Out)
{
	double OutDouble;
	if(JsonAccessor.JsonObject->TryGetNumberField(InFieldName, OutDouble) == false)
	{
		return false;
	}

	Out = (float)OutDouble;
	return true;
}

bool UJsonFunctionLibrary::TryGetFloatArrayField(const FJsonAccessor& JsonAccessor, const FString& InFieldName, TArray<float>& Out)
{
	const TArray<TSharedPtr<FJsonValue>>* OutArray;
	if(JsonAccessor.JsonObject->TryGetArrayField(InFieldName, OutArray) == false)
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
			UE_LOG(LogWebApi, Warning, TEXT("%s array's item is not float."), *InFieldName);
		}
	}
	return true;
}

bool UJsonFunctionLibrary::TryGetStringField(const FJsonAccessor& JsonAccessor, const FString& InFieldName, FString& Out)
{
	return JsonAccessor.JsonObject->TryGetStringField(InFieldName, Out);
}

bool UJsonFunctionLibrary::TryGetStringArrayField(const FJsonAccessor& JsonAccessor, const FString& InFieldName, TArray<FString>& Out)
{
	return JsonAccessor.JsonObject->TryGetStringArrayField(InFieldName, Out);
}

bool UJsonFunctionLibrary::TryGetBoolField(const FJsonAccessor& JsonAccessor, const FString& InFieldName, bool& Out)
{
	return JsonAccessor.JsonObject->TryGetBoolField(InFieldName, Out);
}

bool UJsonFunctionLibrary::TryGetBoolArrayField(const FJsonAccessor& JsonAccessor, const FString& InFieldName, TArray<bool>& Out)
{
	const TArray<TSharedPtr<FJsonValue>>* OutArray;
	if(JsonAccessor.JsonObject->TryGetArrayField(InFieldName, OutArray) == false)
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
			UE_LOG(LogWebApi, Warning, TEXT("%s array's item is not boolean."), *InFieldName);
		}
	}
	return true;
}

bool UJsonFunctionLibrary::TryGetObjectField(const FJsonAccessor& JsonAccessor, const FString& InFieldName, FJsonAccessor& Out)
{
	const TSharedPtr<FJsonObject>* OutObject;
	if(JsonAccessor.JsonObject->TryGetObjectField(InFieldName, OutObject) == false)
	{
		return false;
	}

	Out.FieldName = InFieldName;
	Out.JsonObject = *OutObject;
	return true;
}
