#include "WebApiPrivatePCH.h"
#include "WebApiResponseBodyString.h"

UWebApiResponseBodyString::UWebApiResponseBodyString(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UWebApiResponseBodyString::Copy(const UWebApiResponseBodyBase* Source)
{
	UWebApiResponseBodyBase::Copy(Source);

	auto CastSource = Cast<const UWebApiResponseBodyString>(Source);
	if(CastSource == nullptr) return;

	SetResponse(CastSource->Response);
}

void UWebApiResponseBodyString::SetResponse(const FString& InResponse)
{
	this->Response = InResponse;
}

const FString& UWebApiResponseBodyString::GetResponse() const
{
	return Response;
}
