#include "WebApiResponseBodyToken.h"
#include "liboauthcpp.h"

UWebApiResponseBodyToken::UWebApiResponseBodyToken(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UWebApiResponseBodyToken::GetRequestToken(FString& Token, FString& TokenSecret)
{
	std::string Content(TCHAR_TO_UTF8(*ResponseContent));
	std::size_t pos = Content.find("oauth_token");
	if (pos == std::string::npos)
	{
		return false;
	}

	OAuth::Token RequestToken = OAuth::Token::extract(Content);

	Token = RequestToken.key().c_str();
	TokenSecret = RequestToken.secret().c_str();
	return true;
}
