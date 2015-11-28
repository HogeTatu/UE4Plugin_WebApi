#pragma once

#include "K2Node.h"
#include "K2Node_ConstructObjectFromClass.h"
#include "K2Node_CreateWebApiNodeBase.generated.h"

UCLASS(Abstract)
class WEBAPIEDITOR_API UK2Node_CreateWebApiNodeBase : public UK2Node_ConstructObjectFromClass
{
	GENERATED_UCLASS_BODY()

	// Begin UK2Node interface
	virtual FText GetMenuCategory() const override;
	// End UK2Node interface.
};
