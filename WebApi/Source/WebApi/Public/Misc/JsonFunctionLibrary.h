#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JsonAccessor.h"
#include "JsonFunctionLibrary.generated.h"

/** JSON関連ライブラリ */
UCLASS()
class WEBAPI_API UJsonFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Json")
	static bool TryGetIntField(const FJsonAccessor& JsonAccessor, const FString& FieldName, int32& Out);

	UFUNCTION(BlueprintCallable, Category="Json")
	static bool TryGetIntArrayField(const FJsonAccessor& JsonAccessor, const FString& FieldName, TArray<int32>& Out);

	UFUNCTION(BlueprintCallable, Category="Json")
	static bool TryGetFloatField(const FJsonAccessor& JsonAccessor, const FString& FieldName, float& Out);

	UFUNCTION(BlueprintCallable, Category="Json")
	static bool TryGetFloatArrayField(const FJsonAccessor& JsonAccessor, const FString& FieldName, TArray<float>& Out);

	UFUNCTION(BlueprintCallable, Category="Json")
	static bool TryGetStringField(const FJsonAccessor& JsonAccessor, const FString& FieldName, FString& Out);

	UFUNCTION(BlueprintCallable, Category="Json")
	static bool TryGetStringArrayField(const FJsonAccessor& JsonAccessor, const FString& FieldName, TArray<FString>& Out);

	UFUNCTION(BlueprintCallable, Category="Json")
	static bool TryGetBoolField(const FJsonAccessor& JsonAccessor, const FString& FieldName, bool& Out);

	UFUNCTION(BlueprintCallable, Category="Json")
	static bool TryGetBoolArrayField(const FJsonAccessor& JsonAccessor, const FString& FieldName, TArray<bool>& Out);

	UFUNCTION(BlueprintCallable, Category="Json")
	static bool TryGetObjectField(const FJsonAccessor& JsonAccessor, const FString& FieldName, FJsonAccessor& Out);
};
