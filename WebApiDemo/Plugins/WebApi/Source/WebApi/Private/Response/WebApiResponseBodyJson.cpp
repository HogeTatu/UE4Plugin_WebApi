#include "WebApiResponseBodyJson.h"
#include "WebApiLog.h"
#include "Misc/JsonFunctionLibrary.h"
#include "Json.h"

UWebApiResponseBodyJson::UWebApiResponseBodyJson(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UWebApiResponseBodyJson::GetJsonAccessor(FJsonAccessor& JsonAccessor)
{
	TSharedPtr<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(ResponseContent);

	TSharedPtr<FJsonObject> JsonObject;
	if(FJsonSerializer::Deserialize(JsonReader.ToSharedRef(), JsonObject) == false)
	{
		UE_LOG(LogWebApi, Error, TEXT("FJsonSerializer::Deserialize failed. %s"), *ResponseContent);
		return false;
	}

	JsonAccessor = FJsonAccessor();
	{
		JsonAccessor.FieldName = TEXT("Root");
		JsonAccessor.JsonObject = JsonObject;
	}

	return true;
}
