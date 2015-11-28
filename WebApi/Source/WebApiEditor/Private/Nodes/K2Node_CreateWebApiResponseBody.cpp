#include "WebApiEditorPrivatePCH.h"
#include "KismetCompiler.h"
#include "WebApiResponseBodyBase.h"
#include "K2Node_CreateWebApiResponseBody.h"

#define LOCTEXT_NAMESPACE "WebApi"

struct FK2Node_CreateWebApiResponseBodyHelper
{
	static FString SourcePinName;
};

FString FK2Node_CreateWebApiResponseBodyHelper::SourcePinName(TEXT("Source"));

UK2Node_CreateWebApiResponseBody::UK2Node_CreateWebApiResponseBody(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeTooltip = LOCTEXT("NodeTooltip", "Creates a new WebApiResponseBody");
}

void UK2Node_CreateWebApiResponseBody::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();

	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	// Source pin
	UEdGraphPin* SourcePin = CreatePin(EGPD_Input, K2Schema->PC_Object, TEXT(""), UWebApiResponseBodyBase::StaticClass(), false, false, FK2Node_CreateWebApiResponseBodyHelper::SourcePinName);
	SetPinToolTip(*SourcePin, LOCTEXT("SourcePinDescription", "Property copy source."));
}

void UK2Node_CreateWebApiResponseBody::ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);

	static FName Create_FunctionName = GET_FUNCTION_NAME_CHECKED(UWebApiResponseBodyBase, Create);
	static FString ClassType_ParamName = FString(TEXT("ClassType"));
	static FString Source_ParamName = FString(TEXT("Source"));

	UK2Node_CreateWebApiResponseBody* CreateWebApiResponseBodyNode = this;
	UEdGraphPin* SpawnNodeExec = CreateWebApiResponseBodyNode->GetExecPin();
	UEdGraphPin* SpawnSourcePin = CreateWebApiResponseBodyNode->GetSourcePin();
	UEdGraphPin* SpawnClassPin = CreateWebApiResponseBodyNode->GetClassPin();
	UEdGraphPin* SpawnNodeThen = CreateWebApiResponseBodyNode->GetThenPin();
	UEdGraphPin* SpawnNodeResult = CreateWebApiResponseBodyNode->GetResultPin();

	UClass* SpawnClass = ( SpawnClassPin != NULL ) ? Cast<UClass>(SpawnClassPin->DefaultObject) : NULL;
	if ( ( 0 == SpawnClassPin->LinkedTo.Num() ) && ( NULL == SpawnClass ) )
	{
		CompilerContext.MessageLog.Error(*LOCTEXT("CreateWebApiResponseBodyNodeMissingClass_Error", "Spawn node @@ must have a class specified.").ToString(), CreateWebApiResponseBodyNode);
		// we break exec links so this is the only error we get, don't want the CreateWebApi node being considered and giving 'unexpected node' type warnings
		CreateWebApiResponseBodyNode->BreakAllNodeLinks();
		return;
	}

	//////////////////////////////////////////////////////////////////////////
	// create 'UWebApiResponseBodyBase::Create' call node
	UK2Node_CallFunction* CallCreateNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(CreateWebApiResponseBodyNode, SourceGraph);
	CallCreateNode->FunctionReference.SetExternalMember(Create_FunctionName, UWebApiResponseBodyBase::StaticClass());
	CallCreateNode->AllocateDefaultPins();

	UEdGraphPin* CallCreateExec = CallCreateNode->GetExecPin();
	UEdGraphPin* CallCreateClassTypePin = CallCreateNode->FindPinChecked(ClassType_ParamName);
	UEdGraphPin* CallCreateSourcePin = CallCreateNode->FindPinChecked(Source_ParamName);
	UEdGraphPin* CallCreateResult = CallCreateNode->GetReturnValuePin();

	// Move 'exec' connection from create WebApi node to 'UWebApiResponseBodyBase::Create'
	CompilerContext.MovePinLinksToIntermediate(*SpawnNodeExec, *CallCreateExec);

	if ( SpawnClassPin->LinkedTo.Num() > 0 )
	{
		// Copy the 'blueprint' connection from the spawn node to 'UWebApiResponseBodyBase::Create'
		CompilerContext.MovePinLinksToIntermediate(*SpawnClassPin, *CallCreateClassTypePin);
	}
	else
	{
		// Copy blueprint literal onto 'UWebApiResponseBodyBase::Create' call
		CallCreateClassTypePin->DefaultObject = SpawnClass;
	}

	if ( SpawnSourcePin )
	{
		CompilerContext.MovePinLinksToIntermediate(*SpawnSourcePin, *CallCreateSourcePin);
	}

	// Move result connection from spawn node to 'UWebApiResponseBodyBase::Create'
	CallCreateResult->PinType = SpawnNodeResult->PinType; // Copy type so it uses the right actor subclass
	CompilerContext.MovePinLinksToIntermediate(*SpawnNodeResult, *CallCreateResult);

	//////////////////////////////////////////////////////////////////////////
	// create 'set var' nodes

	// Get 'result' pin from 'begin spawn', this is the actual actor we want to set properties on
	UEdGraphPin* LastThen = FKismetCompilerUtilities::GenerateAssignmentNodes(CompilerContext, SourceGraph, CallCreateNode, CreateWebApiResponseBodyNode, CallCreateResult, GetClassToSpawn());

	// Move 'then' connection from create WebApi node to the last 'then'
	CompilerContext.MovePinLinksToIntermediate(*SpawnNodeThen, *LastThen);

	// Break any links to the expanded node
	CreateWebApiResponseBodyNode->BreakAllNodeLinks();
}

UEdGraphPin* UK2Node_CreateWebApiResponseBody::GetSourcePin() const
{
	UEdGraphPin* Pin = FindPin(FK2Node_CreateWebApiResponseBodyHelper::SourcePinName);
	check(Pin == NULL || Pin->Direction == EGPD_Input);
	return Pin;
}

FText UK2Node_CreateWebApiResponseBody::GetBaseNodeTitle() const
{
	return LOCTEXT("CreateWebApiResponseBody_BaseTitle", "Create WebApiResponseBody");
}

FText UK2Node_CreateWebApiResponseBody::GetNodeTitleFormat() const
{
	return LOCTEXT("CreateWebApiResponseBody", "Create {ClassName}");
}

UClass* UK2Node_CreateWebApiResponseBody::GetClassPinBaseClass() const
{
	return UWebApiResponseBodyBase::StaticClass();
}

bool UK2Node_CreateWebApiResponseBody::IsSpawnVarPin(UEdGraphPin* Pin)
{
	return( Super::IsSpawnVarPin(Pin) &&
		Pin->PinName != FK2Node_CreateWebApiResponseBodyHelper::SourcePinName );
}

#undef LOCTEXT_NAMESPACE
