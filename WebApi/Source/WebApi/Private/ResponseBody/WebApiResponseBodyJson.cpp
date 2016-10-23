#include "WebApiPrivatePCH.h"
#include "WebApiResponseBodyJson.h"

UWebApiResponseBodyJson::UWebApiResponseBodyJson(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UWebApiResponseBodyJson::SetResponse(const FString& InResponse)
{
	UWebApiResponseBodyString::SetResponse(InResponse);

	JsonReader = TJsonReaderFactory<>::Create(InResponse);

	TSharedPtr<FJsonObject> JsonObject;
	if(FJsonSerializer::Deserialize(JsonReader.ToSharedRef(), JsonObject) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("FJsonSerializer::Deserialize failed. %s"), *InResponse);
	}

	RootJsonAccessor = UJsonAccessor::Create(TEXT("Root"), JsonObject);
}

void UWebApiResponseBodyJson::GetRootJsonAccessor(UJsonAccessor*& OutRootJsonAccessor) const
{
	OutRootJsonAccessor = this->RootJsonAccessor;
}
