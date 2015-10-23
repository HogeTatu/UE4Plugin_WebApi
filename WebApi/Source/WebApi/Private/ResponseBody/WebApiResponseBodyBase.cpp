#include "WebApiPrivatePCH.h"
#include "WebApiResponseBodyBase.h"

UWebApiResponseBodyBase::UWebApiResponseBodyBase(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, Code(0)
{
}

UWebApiResponseBodyBase* UWebApiResponseBodyBase::CreateResponseBody(UClass* Class)
{
	return NewObject<UWebApiResponseBodyBase>(GetTransientPackage(), Class);
}

void UWebApiResponseBodyBase::Copy(const UWebApiResponseBodyBase* Source)
{
	Code = Source->Code;
}
