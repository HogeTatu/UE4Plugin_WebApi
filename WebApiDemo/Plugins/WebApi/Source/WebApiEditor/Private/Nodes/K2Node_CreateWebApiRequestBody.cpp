#include "WebApiEditorPrivatePCH.h"
#include "KismetCompiler.h"
#include "WebApiRequestBodyBase.h"
#include "K2Node_CreateWebApiRequestBody.h"

#define LOCTEXT_NAMESPACE "WebApi"

struct FK2Node_CreateWebApiRequestBodyHelper
{
	static FString SourcePinName;
};

FString FK2Node_CreateWebApiRequestBodyHelper::SourcePinName(TEXT("Source"));

UK2Node_CreateWebApiRequestBody::UK2Node_CreateWebApiRequestBody(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeTooltip = LOCTEXT("NodeTooltip", "Creates a new WebApiRequestBody");
}

void UK2Node_CreateWebApiRequestBody::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();

	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	// Source pin
	UEdGraphPin* SourcePin = CreatePin(EGPD_Input, K2Schema->PC_Object, TEXT(""), UWebApiRequestBodyBase::StaticClass(), false, false, FK2Node_CreateWebApiRequestBodyHelper::SourcePinName);
	SetPinToolTip(*SourcePin, LOCTEXT("SourcePinDescription", "Property copy source."));
}

void UK2Node_CreateWebApiRequestBody::ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);

	static FName Create_FunctionName = GET_FUNCTION_NAME_CHECKED(UWebApiRequestBodyBase, Create);
	static FString ClassType_ParamName = FString(TEXT("ClassType"));
	static FString Source_ParamName = FString(TEXT("Source"));

	UK2Node_CreateWebApiRequestBody* CreateWebApiRequestBodyNode = this;
	UEdGraphPin* SpawnNodeExec = CreateWebApiRequestBodyNode->GetExecPin();
	UEdGraphPin* SpawnSourcePin = CreateWebApiRequestBodyNode->GetSourcePin();
	UEdGraphPin* SpawnClassPin = CreateWebApiRequestBodyNode->GetClassPin();
	UEdGraphPin* SpawnNodeThen = CreateWebApiRequestBodyNode->GetThenPin();
	UEdGraphPin* SpawnNodeResult = CreateWebApiRequestBodyNode->GetResultPin();

	UClass* SpawnClass = ( SpawnClassPin != NULL ) ? Cast<UClass>(SpawnClassPin->DefaultObject) : NULL;
	if ( ( 0 == SpawnClassPin->LinkedTo.Num() ) && ( NULL == SpawnClass ) )
	{
		CompilerContext.MessageLog.Error(*LOCTEXT("CreateWebApiRequestBodyNodeMissingClass_Error", "Spawn node @@ must have a class specified.").ToString(), CreateWebApiRequestBodyNode);
		// we break exec links so this is the only error we get, don't want the CreateWebApi node being considered and giving 'unexpected node' type warnings
		CreateWebApiRequestBodyNode->BreakAllNodeLinks();
		return;
	}

	//////////////////////////////////////////////////////////////////////////
	// create 'UWebApiRequestBodyBase::Create' call node
	UK2Node_CallFunction* CallCreateNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(CreateWebApiRequestBodyNode, SourceGraph);
	CallCreateNode->FunctionReference.SetExternalMember(Create_FunctionName, UWebApiRequestBodyBase::StaticClass());
	CallCreateNode->AllocateDefaultPins();

	UEdGraphPin* CallCreateExec = CallCreateNode->GetExecPin();
	UEdGraphPin* CallCreateClassTypePin = CallCreateNode->FindPinChecked(ClassType_ParamName);
	UEdGraphPin* CallCreateSourcePin = CallCreateNode->FindPinChecked(Source_ParamName);
	UEdGraphPin* CallCreateResult = CallCreateNode->GetReturnValuePin();

	// Move 'exec' connection from create WebApi node to 'UWebApiRequestBodyBase::Create'
	CompilerContext.MovePinLinksToIntermediate(*SpawnNodeExec, *CallCreateExec);

	if ( SpawnClassPin->LinkedTo.Num() > 0 )
	{
		// Copy the 'blueprint' connection from the spawn node to 'UWebApiRequestBodyBase::Create'
		CompilerContext.MovePinLinksToIntermediate(*SpawnClassPin, *CallCreateClassTypePin);
	}
	else
	{
		// Copy blueprint literal onto 'UWebApiRequestBodyBase::Create' call
		CallCreateClassTypePin->DefaultObject = SpawnClass;
	}

	if ( SpawnSourcePin )
	{
		CompilerContext.MovePinLinksToIntermediate(*SpawnSourcePin, *CallCreateSourcePin);
	}

	// Move result connection from spawn node to 'UWebApiRequestBodyBase::Create'
	CallCreateResult->PinType = SpawnNodeResult->PinType; // Copy type so it uses the right actor subclass
	CompilerContext.MovePinLinksToIntermediate(*SpawnNodeResult, *CallCreateResult);

	//////////////////////////////////////////////////////////////////////////
	// create 'set var' nodes

	// Get 'result' pin from 'begin spawn', this is the actual actor we want to set properties on
	UEdGraphPin* LastThen = FKismetCompilerUtilities::GenerateAssignmentNodes(CompilerContext, SourceGraph, CallCreateNode, CreateWebApiRequestBodyNode, CallCreateResult, GetClassToSpawn());

	// Move 'then' connection from create WebApi node to the last 'then'
	CompilerContext.MovePinLinksToIntermediate(*SpawnNodeThen, *LastThen);

	// Break any links to the expanded node
	CreateWebApiRequestBodyNode->BreakAllNodeLinks();
}

UEdGraphPin* UK2Node_CreateWebApiRequestBody::GetSourcePin() const
{
	UEdGraphPin* Pin = FindPin(FK2Node_CreateWebApiRequestBodyHelper::SourcePinName);
	check(Pin == NULL || Pin->Direction == EGPD_Input);
	return Pin;
}

FText UK2Node_CreateWebApiRequestBody::GetBaseNodeTitle() const
{
	return LOCTEXT("CreateWebApiRequestBody_BaseTitle", "Create WebApiRequestBody");
}

FText UK2Node_CreateWebApiRequestBody::GetNodeTitleFormat() const
{
	return LOCTEXT("CreateWebApiRequestBody", "Create {ClassName}");
}

UClass* UK2Node_CreateWebApiRequestBody::GetClassPinBaseClass() const
{
	return UWebApiRequestBodyBase::StaticClass();
}

bool UK2Node_CreateWebApiRequestBody::IsSpawnVarPin(UEdGraphPin* Pin)
{
	return( Super::IsSpawnVarPin(Pin) &&
		Pin->PinName != FK2Node_CreateWebApiRequestBodyHelper::SourcePinName );
}

#undef LOCTEXT_NAMESPACE
