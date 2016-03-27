#include "WebApiPrivatePCH.h"
#include "liboauthcpp.h"
#include "WebApiResponseBodyToken.h"

UWebApiResponseBodyToken::UWebApiResponseBodyToken(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UWebApiResponseBodyToken::SetResponse(const FString& Response)
{
	UWebApiResponseBodyString::SetResponse(Response);

	std::string Content(TCHAR_TO_UTF8(*Response));
	std::size_t pos = Content.find("oauth_token");
	if (pos == std::string::npos)
	{
		return;
	}

	OAuth::Token RequestToken = OAuth::Token::extract(Content);

	Token = RequestToken.key().c_str();
	TokenSecret = RequestToken.secret().c_str();
}
