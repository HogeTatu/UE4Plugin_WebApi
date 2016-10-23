#include "WebApiPrivatePCH.h"
#include "Json.h"
#include "WebApiRequestBodyJson.h"

UWebApiRequestBodyJson::UWebApiRequestBodyJson(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SetDefaultHeaders();
}

void UWebApiRequestBodyJson::Copy(const UWebApiRequestBodyBase* Source)
{
	UWebApiRequestBodyUrlParameter::Copy(Source);

	SetDefaultHeaders();
}

bool UWebApiRequestBodyJson::GetRequestBodyAsString(FString& Body) const
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

	for (const auto& Entry : Parameters)
	{
		JsonObject->SetStringField(*Entry.Key, *Entry.Value);
	}

	auto Writer = TJsonWriterFactory<>::Create(&Body);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

	return true;
}

bool UWebApiRequestBodyJson::GetRequestBodyAsBytes(TArray<uint8>& Body) const
{
	UE_LOG(LogTemp, Warning, TEXT("UWebApiRequestBodyJson::GetRequestBodyAsBytes is not supported."));
	return false;
}

void UWebApiRequestBodyJson::SetDefaultHeaders()
{
	SetHeader("Content-Type", "application/json");
}
