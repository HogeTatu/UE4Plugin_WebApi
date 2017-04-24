#include "WebApiRequestBodyJson.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"

UWebApiRequestBodyJson::UWebApiRequestBodyJson(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UWebApiRequestBodyJson::GetRequestBodyAsString(FString& RequestBody) const
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

	for (const auto& RequestParam : RequestParams)
	{
		JsonObject->SetStringField(*RequestParam.Key, *RequestParam.Value);
	}

	auto Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

	return true;
}

void UWebApiRequestBodyJson::SetDefaultRequestHeaders()
{
	Super::SetDefaultRequestHeaders();

	SetRequestHeader("Content-Type", "application/json");
}
