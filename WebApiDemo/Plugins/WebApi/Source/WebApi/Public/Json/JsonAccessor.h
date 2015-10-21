#pragma once

#include "JsonAccessor.generated.h"

UCLASS(ClassGroup=Json, BlueprintType, Blueprintable)
class WEBAPI_API UJsonAccessor : public UObject
{
	GENERATED_BODY()

private:
	// private variable

	FString FieldName;
	TSharedPtr<FJsonObject> JsonObject;

public:
	// constructor

	UJsonAccessor();

	UJsonAccessor(const FObjectInitializer& ObjectInitializer);

public:
	// public function

	static UJsonAccessor* Create(const FString& FieldName, const TSharedPtr<FJsonObject>& JsonObject);

	UFUNCTION(BlueprintPure, Category="Json")
	const FString& GetFieldName() const;

	const TSharedPtr<FJsonObject>& GetJsonObject() const;

	UFUNCTION(BlueprintPure, Category="Json")
	bool TryGetIntField(const FString& FieldName, int32& Out) const;

	UFUNCTION(BlueprintPure, Category="Json")
	bool TryGetIntArrayField(const FString& FieldName, TArray<int32>& Out) const;

	UFUNCTION(BlueprintPure, Category="Json")
	bool TryGetFloatField(const FString& FieldName, float& Out) const;

	UFUNCTION(BlueprintPure, Category="Json")
	bool TryGetFloatArrayField(const FString& FieldName, TArray<float>& Out) const;

	UFUNCTION(BlueprintPure, Category="Json")
	bool TryGetStringField(const FString& FieldName, FString& Out) const;

	UFUNCTION(BlueprintPure, Category="Json")
	bool TryGetStringArrayField(const FString& FieldName, TArray<FString>& Out) const;

	UFUNCTION(BlueprintPure, Category="Json")
	bool TryGetBoolField(const FString& FieldName, bool& Out) const;

	UFUNCTION(BlueprintPure, Category="Json")
	bool TryGetBoolArrayField(const FString& FieldName, TArray<bool>& Out) const;

	UFUNCTION(BlueprintPure, Category="Json")
	bool TryGetObjectField(const FString& FieldName, UJsonAccessor*& Out) const;
};
