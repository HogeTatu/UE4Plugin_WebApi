#pragma once

#include "WebApiPostFilterInterface.generated.h"

class UWebApiResponseBodyBase;

UINTERFACE()
class WEBAPI_API UWebApiPostFilterInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class WEBAPI_API IWebApiPostFilterInterface
{
	GENERATED_IINTERFACE_BODY()

	UFUNCTION(BlueprintNativeEvent, Category="Network|WebApi")
	UWebApiResponseBodyBase* ExecuteWebApiPostFilter(UWebApiResponseBodyBase* ResponseBody);
};
