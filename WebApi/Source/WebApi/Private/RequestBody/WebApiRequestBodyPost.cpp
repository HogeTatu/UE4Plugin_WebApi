#include "WebApiPrivatePCH.h"
#include "Json.h"
#include "WebApiRequestBodyPost.h"

#define LOG_CATEGORY LogTemp

UWebApiRequestBodyPost::UWebApiRequestBodyPost(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SetDefaultHeaders();
}

void UWebApiRequestBodyPost::Copy(const UWebApiRequestBodyBase* Source)
{
	UWebApiRequestBodyUrlParameter::Copy(Source);

	SetDefaultHeaders();
}

bool UWebApiRequestBodyPost::GetRequestBodyAsString(FString& Body) const
{
	return UWebApiRequestBodyUrlParameter::GetRequestBodyAsString(Body);
}

bool UWebApiRequestBodyPost::GetRequestBodyAsBytes(TArray<uint8>& Body) const
{
	UE_LOG(LOG_CATEGORY, Warning, TEXT("UWebApiRequestBodyPost::GetRequestBodyAsBytes is not supported."));
	return false;
}

void UWebApiRequestBodyPost::SetDefaultHeaders()
{
	SetHeader("Content-Type", "application/x-www-form-urlencoded");
}
