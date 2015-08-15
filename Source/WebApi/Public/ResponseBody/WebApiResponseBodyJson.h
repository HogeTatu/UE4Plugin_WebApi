#pragma once

#include "WebApiResponseBodyString.h"
#include "WebApiResponseBodyJson.generated.h"

UCLASS(ClassGroup=WebApi, BlueprintType, Blueprintable)
class WEBAPI_API UWebApiJsonResponseObject : public UObject
{
	GENERATED_UCLASS_BODY()

private:
	// private variable

	FString FieldName;
	TSharedPtr<FJsonObject> JsonObject;

public:
	// public function

	static UWebApiJsonResponseObject* Create(const FString& FieldName, const TSharedPtr<FJsonObject>& JsonObject);

	UFUNCTION(BlueprintPure, Category="WebApi")
	const FString& GetFieldName() const;

	const TSharedPtr<FJsonObject>& GetJsonObject() const;

	UFUNCTION(BlueprintPure, Category="WebApi")
	bool TryGetIntField(const FString& FieldName, int32& Out) const;

	UFUNCTION(BlueprintPure, Category="WebApi")
	bool TryGetIntArrayField(const FString& FieldName, TArray<int32>& Out) const;

	UFUNCTION(BlueprintPure, Category="WebApi")
	bool TryGetFloatField(const FString& FieldName, float& Out) const;

	UFUNCTION(BlueprintPure, Category="WebApi")
	bool TryGetFloatArrayField(const FString& FieldName, TArray<float>& Out) const;

	UFUNCTION(BlueprintPure, Category="WebApi")
	bool TryGetStringField(const FString& FieldName, FString& Out) const;

	UFUNCTION(BlueprintPure, Category="WebApi")
	bool TryGetStringArrayField(const FString& FieldName, TArray<FString>& Out) const;

	UFUNCTION(BlueprintPure, Category="WebApi")
	bool TryGetBoolField(const FString& FieldName, bool& Out) const;

	UFUNCTION(BlueprintPure, Category="WebApi")
	bool TryGetBoolArrayField(const FString& FieldName, TArray<bool>& Out) const;

	UFUNCTION(BlueprintPure, Category="WebApi")
	bool TryGetObjectField(const FString& FieldName, UWebApiJsonResponseObject*& Out) const;
};

///

UCLASS(ClassGroup=WebApi, BlueprintType, Blueprintable)
class WEBAPI_API UWebApiResponseBodyJson : public UWebApiResponseBodyString
{
	GENERATED_UCLASS_BODY()

private:
	// private variable

	TSharedPtr<TJsonReader<>> JsonReader;
	UWebApiJsonResponseObject* RootJsonResponseObject;

public:
	// public function

	virtual void SetResponse(const FString& Response) override;

	UFUNCTION(BlueprintCallable, Category="WebApi")
	void GetRootJsonResponseObject(UWebApiJsonResponseObject*& RootJsonResponseObject) const;
};
