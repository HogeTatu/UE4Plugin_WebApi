#include "WebApiDummyRequestFilter.h"

UWebApiDummyRequestFilter* UWebApiDummyRequestFilter::GetDummyRequestFilter()
{
	return StaticClass()->GetDefaultObject<UWebApiDummyRequestFilter>();
}

UWebApiRequestBody* UWebApiDummyRequestFilter::ExecuteRequestFilter_Implementation(UWebApiRequestBody* Request)
{
	Request->IsDummyRequest = true;
	return Request;
}
