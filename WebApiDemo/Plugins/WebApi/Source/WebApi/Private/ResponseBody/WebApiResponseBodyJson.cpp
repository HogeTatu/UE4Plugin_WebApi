#include "WebApiPrivatePCH.h"
#include "WebApiResponseBodyJson.h"

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

	RootJsonAccessor = UJsonAccessor::Create(TEXT("Root"), JsonObject);
}

void UWebApiResponseBodyJson::GetRootJsonAccessor(UJsonAccessor*& RootJsonAccessor) const
{
	RootJsonAccessor = this->RootJsonAccessor;
}
