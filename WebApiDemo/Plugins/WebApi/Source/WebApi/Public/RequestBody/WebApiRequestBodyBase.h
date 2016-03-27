#pragma once

#include "WebApiRequestBodyBase.generated.h"

namespace EWebApiRequestType
{
	enum Type
	{
		GET,
		PUT,
		POST,
	};

	static const TCHAR* ToString(const EWebApiRequestType::Type& Type)
	{
		switch (Type)
		{
		case GET:
			return TEXT("GET");
		case PUT:
			return TEXT("PUT");
		case POST:
			return TEXT("POST");
		}
		return TEXT("");
	}
}

namespace EWebApiRequestParameterType
{
	enum Type
	{
		STRING,
		BYTES,
	};
}

UCLASS(ClassGroup=WebApi, Abstract, BlueprintType, Blueprintable)
class WEBAPI_API UWebApiRequestBodyBase : public UObject
{
	GENERATED_UCLASS_BODY()

protected:
	// protected variable

	TMap<FString, FString> Headers;

public:
	// public function

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, meta=(DisplayName="Create WebApi Request Body", BlueprintInternalUseOnly="true"), Category="Network|WebApi")
	static UWebApiRequestBodyBase* Create(TSubclassOf<class UWebApiRequestBodyBase> ClassType, const UWebApiRequestBodyBase* Source = nullptr);

	virtual EWebApiRequestType::Type GetRequestType() const { return EWebApiRequestType::GET; };
	virtual EWebApiRequestParameterType::Type GetRequestParameterType() const  { return EWebApiRequestParameterType::STRING; };

	virtual bool GetRequestBodyAsString(FString& Body) const { return false; };
	virtual bool GetRequestBodyAsBytes(TArray<uint8>& Body) const { return false; };

	UFUNCTION(BlueprintCallable, Category="Network|WebApi", meta=(DisplayName = "CopyRequestBody"))
	virtual void Copy(const UWebApiRequestBodyBase* Source);

	UFUNCTION(BlueprintCallable, Category="Network|WebApi")
	void SetHeader(const FString& Key, const FString& Value);

	UFUNCTION(BlueprintPure, Category="Network|WebApi")
	const FString& GetHeader(const FString& Key) const;

	virtual const TMap<FString, FString>& GetHeaders() const;
};
