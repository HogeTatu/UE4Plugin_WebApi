#include "WebApiConvToOAuthFilter.h"
#include "WebApiLog.h"
#include "Request/WebApiRequestBodyOAuth.h"
#include "Response/WebApiResponseBodyToken.h"
#include "Misc/PropertyFunctionLibrary.h"

UWebApiConvToOAuthFilter* UWebApiConvToOAuthFilter::GetConvToOAuthFilter()
{
	return StaticClass()->GetDefaultObject<UWebApiConvToOAuthFilter>();
}

UWebApiRequestBody* UWebApiConvToOAuthFilter::ExecuteRequestFilter_Implementation(UWebApiRequestBody* Request)
{
	auto RequestUrlParam = Cast<UWebApiRequestBodyUrlParam>(Request);
	if (!RequestUrlParam)
	{
		UE_LOG(LogWebApi, Warning, TEXT("Request is not UWebApiRequestBodyUrlParam"));
		return Request;
	}

	auto RequestOAuth = UWebApiRequestBody::Create<UWebApiRequestBodyOAuth>();

	// プロパティコピー
	auto PropertyNames = UWebApiRequestBody::GetPropertyNames(UWebApiRequestBodyUrlParam::StaticClass());
	UPropertyFunctionLibrary::CopyObjectProperties(RequestUrlParam, RequestOAuth, PropertyNames);

	return RequestOAuth;
}

UWebApiResponseBody* UWebApiConvToOAuthFilter::ExecuteResponseFilter_Implementation(UWebApiResponseBody* Response)
{
	auto ResponseString = Cast<UWebApiResponseBodyString>(Response);
	if (!ResponseString)
	{
		UE_LOG(LogWebApi, Warning, TEXT("Response is not UWebApiResponseBodyString"));
		return Response;
	}

	auto ResponseToken = UWebApiResponseBody::Create<UWebApiResponseBodyToken>();

	// プロパティコピー
	auto PropertyNames = UWebApiResponseBody::GetPropertyNames(UWebApiResponseBodyString::StaticClass());
	UPropertyFunctionLibrary::CopyObjectProperties(ResponseString, ResponseToken, PropertyNames);

	return ResponseToken;
}
