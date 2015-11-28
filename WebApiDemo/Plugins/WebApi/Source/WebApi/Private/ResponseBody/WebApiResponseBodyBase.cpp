#include "WebApiPrivatePCH.h"
#include "WebApiResponseBodyBase.h"

UWebApiResponseBodyBase::UWebApiResponseBodyBase(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, Code(0)
{
}

UWebApiResponseBodyBase* UWebApiResponseBodyBase::Create(TSubclassOf<class UWebApiResponseBodyBase> ClassType, const UWebApiResponseBodyBase* Source)
{
	auto Instance = NewObject<UWebApiResponseBodyBase>(GetTransientPackage(), ClassType);

	if (Source != nullptr)
	{
		Instance->Copy(Source);
	}

	return Instance;
}

void UWebApiResponseBodyBase::Copy(const UWebApiResponseBodyBase* Source)
{
	Code = Source->Code;
}
