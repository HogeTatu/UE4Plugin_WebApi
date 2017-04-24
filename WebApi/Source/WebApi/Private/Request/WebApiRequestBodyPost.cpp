#include "WebApiRequestBodyPost.h"

UWebApiRequestBodyPost::UWebApiRequestBodyPost(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UWebApiRequestBodyPost::SetDefaultRequestHeaders()
{
	Super::SetDefaultRequestHeaders();

	SetRequestHeader("Content-Type", "application/x-www-form-urlencoded");
}
