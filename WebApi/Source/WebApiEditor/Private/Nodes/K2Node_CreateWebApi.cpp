#include "WebApiEditorPrivatePCH.h"
#include "KismetCompiler.h"
#include "WebApi.h"
#include "K2Node_CreateWebApi.h"

#define LOCTEXT_NAMESPACE "WebApi"

UK2Node_CreateWebApi::UK2Node_CreateWebApi(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeTooltip = LOCTEXT("NodeTooltip", "Creates a new WebApi");
}

void UK2Node_CreateWebApi::ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);

	static FName Create_FunctionName = GET_FUNCTION_NAME_CHECKED(UWebApi, Create);
	static FString ClassType_ParamName = FString(TEXT("ClassType"));

	UK2Node_CreateWebApi* CreateWebApiNode = this;
	UEdGraphPin* SpawnNodeExec = CreateWebApiNode->GetExecPin();
	UEdGraphPin* SpawnClassPin = CreateWebApiNode->GetClassPin();
	UEdGraphPin* SpawnNodeThen = CreateWebApiNode->GetThenPin();
	UEdGraphPin* SpawnNodeResult = CreateWebApiNode->GetResultPin();

	UClass* SpawnClass = ( SpawnClassPin != NULL ) ? Cast<UClass>(SpawnClassPin->DefaultObject) : NULL;
	if ( ( 0 == SpawnClassPin->LinkedTo.Num() ) && ( NULL == SpawnClass ) )
	{
		CompilerContext.MessageLog.Error(*LOCTEXT("CreateWebApiNodeMissingClass_Error", "Spawn node @@ must have a class specified.").ToString(), CreateWebApiNode);
		// we break exec links so this is the only error we get, don't want the CreateWebApi node being considered and giving 'unexpected node' type warnings
		CreateWebApiNode->BreakAllNodeLinks();
		return;
	}

	//////////////////////////////////////////////////////////////////////////
	// create 'UWebApi::Create' call node
	UK2Node_CallFunction* CallCreateNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(CreateWebApiNode, SourceGraph);
	CallCreateNode->FunctionReference.SetExternalMember(Create_FunctionName, UWebApi::StaticClass());
	CallCreateNode->AllocateDefaultPins();

	UEdGraphPin* CallCreateExec = CallCreateNode->GetExecPin();
	UEdGraphPin* CallCreateClassTypePin = CallCreateNode->FindPinChecked(ClassType_ParamName);
	UEdGraphPin* CallCreateResult = CallCreateNode->GetReturnValuePin();

	// Move 'exec' connection from create WebApi node to 'UWebApi::Create'
	CompilerContext.MovePinLinksToIntermediate(*SpawnNodeExec, *CallCreateExec);

	if ( SpawnClassPin->LinkedTo.Num() > 0 )
	{
		// Copy the 'blueprint' connection from the spawn node to 'UWebApi::Create'
		CompilerContext.MovePinLinksToIntermediate(*SpawnClassPin, *CallCreateClassTypePin);
	}
	else
	{
		// Copy blueprint literal onto 'UWebApi::Create' call
		CallCreateClassTypePin->DefaultObject = SpawnClass;
	}

	// Move result connection from spawn node to 'UWebApi::Create'
	CallCreateResult->PinType = SpawnNodeResult->PinType; // Copy type so it uses the right actor subclass
	CompilerContext.MovePinLinksToIntermediate(*SpawnNodeResult, *CallCreateResult);

	//////////////////////////////////////////////////////////////////////////
	// create 'set var' nodes

	// Get 'result' pin from 'begin spawn', this is the actual actor we want to set properties on
	UEdGraphPin* LastThen = FKismetCompilerUtilities::GenerateAssignmentNodes(CompilerContext, SourceGraph, CallCreateNode, CreateWebApiNode, CallCreateResult, GetClassToSpawn());

	// Move 'then' connection from create WebApi node to the last 'then'
	CompilerContext.MovePinLinksToIntermediate(*SpawnNodeThen, *LastThen);

	// Break any links to the expanded node
	CreateWebApiNode->BreakAllNodeLinks();
}

FText UK2Node_CreateWebApi::GetBaseNodeTitle() const
{
	return LOCTEXT("CreateWebApi_BaseTitle", "Create WebApi");
}

FText UK2Node_CreateWebApi::GetNodeTitleFormat() const
{
	return LOCTEXT("CreateWebApi", "Create {ClassName}");
}

UClass* UK2Node_CreateWebApi::GetClassPinBaseClass() const
{
	return UWebApi::StaticClass();
}

#undef LOCTEXT_NAMESPACE
