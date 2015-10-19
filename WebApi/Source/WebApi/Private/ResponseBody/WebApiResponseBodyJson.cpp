#include "WebApiPrivatePCH.h"
#include "Json.h"
#include "WebApiResponseBodyJson.h"

UWebApiJsonResponseObject::UWebApiJsonResponseObject(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UWebApiJsonResponseObject* UWebApiJsonResponseObject::Create(const FString& FieldName, const TSharedPtr<FJsonObject>& JsonObject)
{
	auto Instance = (UWebApiJsonResponseObject*)NewObject<UObject>(GetTransientPackage(), UWebApiJsonResponseObject::StaticClass());
	Instance->FieldName = FieldName;
	Instance->JsonObject = JsonObject;
	return Instance;
}

const FString& UWebApiJsonResponseObject::GetFieldName() const
{
	return FieldName;
}

const TSharedPtr<FJsonObject>& UWebApiJsonResponseObject::GetJsonObject() const
{
	return JsonObject;
}

bool UWebApiJsonResponseObject::TryGetIntField(const FString& FieldName, int32& Out) const
{
	check(JsonObject.IsValid());
	return JsonObject->TryGetNumberField(FieldName, Out);
}

bool UWebApiJsonResponseObject::TryGetIntArrayField(const FString& FieldName, TArray<int32>& Out) const
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

bool UWebApiJsonResponseObject::TryGetFloatField(const FString& FieldName, float& Out) const
{
	double OutDouble;
	if(JsonObject->TryGetNumberField(FieldName, OutDouble) == false)
	{
		return false;
	}

	Out = (float)OutDouble;
	return true;
}

bool UWebApiJsonResponseObject::TryGetFloatArrayField(const FString& FieldName, TArray<float>& Out) const
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

bool UWebApiJsonResponseObject::TryGetStringField(const FString& FieldName, FString& Out) const
{
	return JsonObject->TryGetStringField(FieldName, Out);
}

bool UWebApiJsonResponseObject::TryGetStringArrayField(const FString& FieldName, TArray<FString>& Out) const
{
	return JsonObject->TryGetStringArrayField(FieldName, Out);
}

bool UWebApiJsonResponseObject::TryGetBoolField(const FString& FieldName, bool& Out) const
{
	return JsonObject->TryGetBoolField(FieldName, Out);
}

bool UWebApiJsonResponseObject::TryGetBoolArrayField(const FString& FieldName, TArray<bool>& Out) const
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

bool UWebApiJsonResponseObject::TryGetObjectField(const FString& FieldName, UWebApiJsonResponseObject*& Out) const
{
	const TSharedPtr<FJsonObject>* OutObject;
	if(JsonObject->TryGetObjectField(FieldName, OutObject) == false)
	{
		return false;
	}

	Out = Create(FieldName, *OutObject);
	return true;
}

///

UWebApiResponseBodyJson::UWebApiResponseBodyJson(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UWebApiResponseBodyJson::SetResponse(const FString& Response)
{
	UWebApiResponseBodyString::SetResponse(Response);

	JsonReader = TJsonReaderFactory<>::Create(Response);

	TSharedPtr<FJsonObject> JsonObject;
	if(FJsonSerializer::Deserialize(JsonReader.ToSharedRef(), JsonObject) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("FJsonSerializer::Deserialize failed. %s"), *Response);
	}

	RootJsonResponseObject = UWebApiJsonResponseObject::Create(TEXT("Root"), JsonObject);
}

void UWebApiResponseBodyJson::GetRootJsonResponseObject(UWebApiJsonResponseObject*& RootJsonResponseObject) const
{
	RootJsonResponseObject = this->RootJsonResponseObject;
}
