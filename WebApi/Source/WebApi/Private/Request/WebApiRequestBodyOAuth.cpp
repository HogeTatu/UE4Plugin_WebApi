#include "WebApiRequestBodyOAuth.h"
#include "WebApiLog.h"
#include "liboauthcpp.h"
#include "urlencode.h"

UWebApiRequestBodyOAuth::UWebApiRequestBodyOAuth(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UWebApiRequestBodyOAuth::SetAuthHeader(const FOAuthParam& Param)
{
	std::string RawUrl(TCHAR_TO_UTF8(*Param.Url));
	OAuth::Consumer Consumer(TCHAR_TO_UTF8(*Param.ConsumerKey), TCHAR_TO_UTF8(*Param.ConsumerSecret));

	FString Body;
	GetRequestBodyAsString(Body);
	std::string RawBody = TCHAR_TO_UTF8(*Body);

	FString Authorization;
	if (Param.Token.IsEmpty() || Param.TokenSecret.IsEmpty())
	{
		OAuth::Client OAuth = OAuth::Client(&Consumer);
		Authorization += OAuth.getHttpHeader(OAuth::Http::Post, RawUrl, RawBody).c_str();
	}
	else
	{
		OAuth::Token Token(TCHAR_TO_UTF8(*Param.Token), TCHAR_TO_UTF8(*Param.TokenSecret));
		bool IsEnabledPin = !Param.Pin.IsEmpty();

		if (IsEnabledPin)
		{
			Token.setPin(TCHAR_TO_UTF8(*Param.Pin));
		}

		OAuth::Client OAuth = OAuth::Client(&Consumer, &Token);
		Authorization += OAuth.getHttpHeader(OAuth::Http::Post, RawUrl, RawBody, IsEnabledPin).c_str();
	}

	SetRequestHeader("Authorization", Authorization);
	SetRequestHeader("Content-Length", FString::FromInt(Body.Len()));

	UE_LOG(LogWebApi, Log, TEXT("Authorization : %s"), *GetRequestHeader("Authorization"));
	UE_LOG(LogWebApi, Log, TEXT("Content : %s"), *Body);
	UE_LOG(LogWebApi, Log, TEXT("Content-Length : %d"), Body.Len());
}
