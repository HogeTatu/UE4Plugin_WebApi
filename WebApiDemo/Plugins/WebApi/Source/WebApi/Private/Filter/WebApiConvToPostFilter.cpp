#include "WebApiConvToPostFilter.h"
#include "WebApiLog.h"
#include "Request/WebApiRequestBodyPost.h"
#include "Misc/PropertyFunctionLibrary.h"

UWebApiConvToPostFilter* UWebApiConvToPostFilter::GetConvToPostFilter()
{
	return StaticClass()->GetDefaultObject<UWebApiConvToPostFilter>();
}

UWebApiRequestBody* UWebApiConvToPostFilter::ExecuteRequestFilter_Implementation(UWebApiRequestBody* Request)
{
	auto RequestUrlParam = Cast<UWebApiRequestBodyUrlParam>(Request);
	if (!RequestUrlParam)
	{
		UE_LOG(LogWebApi, Warning, TEXT("Request is not UWebApiRequestBodyUrlParam"));
		return Request;
	}

	auto RequestPost = UWebApiRequestBody::Create<UWebApiRequestBodyPost>();

	// プロパティコピー
	auto PropertyNames = UWebApiRequestBody::GetPropertyNames(UWebApiRequestBodyUrlParam::StaticClass());
	UPropertyFunctionLibrary::CopyObjectProperties(RequestUrlParam, RequestPost, PropertyNames);

	return RequestPost;
}
