#include "WebApiPrivatePCH.h"
#include "liboauthcpp.h"
#include "urlencode.h"
#include "WebApiRequestBodyOAuth.h"

#define LOG_CATEGORY LogTemp

UWebApiRequestBodyOAuth::UWebApiRequestBodyOAuth(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UWebApiRequestBodyOAuth::Copy(const UWebApiRequestBodyBase* Source)
{
	UWebApiRequestBodyPost::Copy(Source);
}

bool UWebApiRequestBodyOAuth::GetRequestBodyAsString(FString& Body) const
{
	return UWebApiRequestBodyPost::GetRequestBodyAsString(Body);
}

bool UWebApiRequestBodyOAuth::GetRequestBodyAsBytes(TArray<uint8>& Body) const
{
	UE_LOG(LOG_CATEGORY, Warning, TEXT("UWebApiRequestBodyOAuth::GetRequestBodyAsBytes is not supported."));
	return false;
}

void UWebApiRequestBodyOAuth::SetAuthHeader(const FOAuthParameter& Param)
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

	SetHeader("Authorization", Authorization);
	SetHeader("Content-Length", FString::FromInt(Body.Len()));

	UE_LOG(LogTemp, Log, TEXT("Authorization : %s"), *GetHeader("Authorization"));
	UE_LOG(LogTemp, Log, TEXT("Content : %s"), *Body);
	UE_LOG(LogTemp, Log, TEXT("Content-Length : %d"), Body.Len());
}
