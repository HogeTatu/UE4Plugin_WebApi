#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuthFunctionLibrary.generated.h"

UCLASS(BlueprintType, MinimalAPI)
class UAuthFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION(BlueprintPure, Category="Network|WebApi|Auth")
	static FString GetAuthorizeUrl(const FString& RequestToken);

	UFUNCTION(BlueprintPure, Category="Network|WebApi|Auth")
	static FString Base64Encode(const TArray<uint8>& Source);

	UFUNCTION(BlueprintPure, Category="Network|WebApi|Auth")
	static FString UrlEncode(const FString& Source);
};
