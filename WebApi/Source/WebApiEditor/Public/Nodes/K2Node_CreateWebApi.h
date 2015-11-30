﻿#pragma once

#include "K2Node_CreateWebApiNodeBase.h"
#include "K2Node_CreateWebApi.generated.h"

UCLASS()
class WEBAPIEDITOR_API UK2Node_CreateWebApi : public UK2Node_CreateWebApiNodeBase
{
	GENERATED_UCLASS_BODY()

	// Begin UEdGraphNode interface.
	virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
	// End UEdGraphNode interface.

protected:
	/** Gets the default node title when no class is selected */
	virtual FText GetBaseNodeTitle() const override;
	/** Gets the node title when a class has been selected. */
	virtual FText GetNodeTitleFormat() const override;
	/** Gets base class to use for the 'class' pin.  UObject by default. */
	virtual UClass* GetClassPinBaseClass() const override;
};