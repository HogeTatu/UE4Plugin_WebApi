#include "WebApiConvToJsonFilter.h"
#include "WebApiLog.h"
#include "Request/WebApiRequestBodyJson.h"
#include "Response/WebApiResponseBodyJson.h"
#include "Misc/PropertyFunctionLibrary.h"

UWebApiConvToJsonFilter* UWebApiConvToJsonFilter::GetConvToJsonFilter()
{
	return StaticClass()->GetDefaultObject<UWebApiConvToJsonFilter>();
}

UWebApiRequestBody* UWebApiConvToJsonFilter::ExecuteRequestFilter_Implementation(UWebApiRequestBody* Request)
{
	auto RequestUrlParam = Cast<UWebApiRequestBodyUrlParam>(Request);
	if (!RequestUrlParam)
	{
		UE_LOG(LogWebApi, Warning, TEXT("Request is not UWebApiRequestBodyUrlParam"));
		return Request;
	}

	auto RequestJson = UWebApiRequestBody::Create<UWebApiRequestBodyJson>();

	// プロパティコピー
	auto PropertyNames = UWebApiRequestBody::GetPropertyNames(UWebApiRequestBodyUrlParam::StaticClass());
	UPropertyFunctionLibrary::CopyObjectProperties(RequestUrlParam, RequestJson, PropertyNames);

	return RequestJson;
}

UWebApiResponseBody* UWebApiConvToJsonFilter::ExecuteResponseFilter_Implementation(UWebApiResponseBody* Response)
{
	auto ResponseString = Cast<UWebApiResponseBodyString>(Response);
	if (!ResponseString)
	{
		UE_LOG(LogWebApi, Warning, TEXT("Response is not UWebApiResponseBodyString"));
		return Response;
	}

	auto ResponseJson = UWebApiResponseBody::Create<UWebApiResponseBodyJson>();

	// プロパティコピー
	auto PropertyNames = UWebApiResponseBody::GetPropertyNames(UWebApiResponseBodyString::StaticClass());
	UPropertyFunctionLibrary::CopyObjectProperties(ResponseString, ResponseJson, PropertyNames);

	return ResponseJson;
}
