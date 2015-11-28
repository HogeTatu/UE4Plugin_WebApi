#include "WebApiEditorPrivatePCH.h"
#include "KismetCompiler.h"
#include "K2Node_CreateWebApiNodeBase.h"

#define LOCTEXT_NAMESPACE "WebApi"

UK2Node_CreateWebApiNodeBase::UK2Node_CreateWebApiNodeBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FText UK2Node_CreateWebApiNodeBase::GetMenuCategory() const
{
	return LOCTEXT("CreateWebApi_MenuCategory", "Network|WebApi");
}

#undef LOCTEXT_NAMESPACE
