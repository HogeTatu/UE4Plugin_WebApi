#pragma once

#include "WebApiPreFilterInterface.generated.h"

class UWebApiRequestBodyBase;

UINTERFACE()
class WEBAPI_API UWebApiPreFilterInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class WEBAPI_API IWebApiPreFilterInterface
{
	GENERATED_IINTERFACE_BODY()

	UFUNCTION(BlueprintNativeEvent, Category="WebApi")
	UWebApiRequestBodyBase* ExecuteWebApiPreFilter(UWebApiRequestBodyBase* RequestBody);
};
