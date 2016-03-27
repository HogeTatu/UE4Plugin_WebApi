#include "WebApiPrivatePCH.h"
#include "WebApiResponseBodyString.h"
#include "WebApi.h"

UWebApi::UWebApi(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, RequestBodyOrg(nullptr)
	, bProcessing(false)
{
	SuccessResponseCodes.Add(200);
}

void UWebApi::PostInitProperties()
{
	Super::PostInitProperties();

	if (!HasAnyFlags(RF_ClassDefaultObject))
	{
		RequestBodyOrg = NewObject<UWebApiRequestBodyUrlParameter>(GetTransientPackage(), UWebApiRequestBodyUrlParameter::StaticClass());
	}
}

UWebApi* UWebApi::Create(TSubclassOf<class UWebApi> ClassType)
{
	return NewObject<UWebApi>(GetTransientPackage(), ClassType);
}

FString UWebApi::GetRequestURL() const
{
	return Domain + "/" + Path;
}

void UWebApi::SetRequestParameter(const FString& Key, const FString& Value)
{
	RequestBodyOrg->SetParameter(Key, Value);
}

const FString& UWebApi::GetRequestParameter(const FString& Key) const
{
	return RequestBodyOrg->GetParameter(Key);
}

void UWebApi::AddPreFilter(const TScriptInterface<IWebApiPreFilterInterface>& PreFilter)
{
	PreFilters.Enqueue(PreFilter.GetObject());
}

void UWebApi::AddPostFilter(const TScriptInterface<IWebApiPostFilterInterface>& PostFilter)
{
	PostFilters.Enqueue(PostFilter.GetObject());
}

void UWebApi::OnPreProcessRequest_Implementation()
{
}

bool UWebApi::ProcessRequest()
{
	if(bProcessing)
	{
		UE_LOG(LogTemp, Warning, TEXT("Request is processing already."));
		return false;
	}

	OnPreProcessRequest();

	UWebApiRequestBodyBase* RequestBody = RequestBodyOrg;
	while (PreFilters.IsEmpty() == false)
	{
		UObject* PreFilter = nullptr;
		if(PreFilters.Dequeue(PreFilter))
		{
			RequestBody = IWebApiPreFilterInterface::Execute_ExecuteWebApiPreFilter(PreFilter, RequestBody);
			if( RequestBody == nullptr )
			{
				UE_LOG(LogTemp, Error, TEXT("RequestBody is null."));
			}
		}
	}

	auto& Module = FHttpModule::Get();
	auto& Manager = Module.GetHttpManager();

	FHttpRequestPtr ProcessingRequest = Module.CreateRequest();

	auto RequestType = RequestBody->GetRequestType();
	ProcessingRequest->SetVerb(EWebApiRequestType::ToString(RequestType));

	FString Url = GetRequestURL();

	if(RequestType == EWebApiRequestType::GET)
	{
		auto UrlParameter = (UWebApiRequestBodyUrlParameter*)RequestBody;
		if(UrlParameter->GetParameterCount() > 0)
		{
			FString ContentString;
			if(RequestBody->GetRequestBodyAsString(ContentString))
			{
				ProcessingRequest->SetURL(Url + TEXT("?") + ContentString);
			}
			else
			{
				ProcessingRequest->SetURL(Url);
			}
		}
		else
		{
			ProcessingRequest->SetURL(Url);
		}
	}
	else
	{
		ProcessingRequest->SetURL(Url);

		switch (RequestBody->GetRequestParameterType())
		{
		case EWebApiRequestParameterType::STRING:
		{
			FString ContentString;
			if(RequestBody->GetRequestBodyAsString(ContentString))
			{
				ProcessingRequest->SetContentAsString(ContentString);
			}
			break;
		}
		case EWebApiRequestParameterType::BYTES:
		{
			TArray<uint8> ContentBytes;
			if(RequestBody->GetRequestBodyAsBytes(ContentBytes))
			{
				ProcessingRequest->SetContent(ContentBytes);
			}
			break;
		}
		}
	}

	for (const auto& Entry : RequestBody->GetHeaders())
	{
		ProcessingRequest->SetHeader(Entry.Key, Entry.Value);
	}

	ProcessingRequest->OnProcessRequestComplete().BindUObject(this, &UWebApi::OnRequestCompletedInternal);
	ProcessingRequest->OnRequestProgress().BindUObject(this, &UWebApi::OnRequestProgressInternal);

	ProcessingRequest->ProcessRequest();

	Manager.AddRequest(ProcessingRequest.ToSharedRef());
	if(Manager.IsValidRequest(ProcessingRequest.Get()) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("Add request failed."));
		ProcessingRequest->CancelRequest();
		return false;
	}

	bProcessing = true;

	OnRequestStart.Broadcast(this);

	return true;
}

void UWebApi::CancelRequest()
{
	if(bProcessing == false)
	{
		return;
	}

	ProcessingRequest->CancelRequest();
	bProcessing = false;
}

bool UWebApi::IsProcessingRequest() const
{
	return bProcessing;
}

void UWebApi::OnRequestCompletedInternal(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccessed)
{
	auto& Module = FHttpModule::Get();
	auto& Manager = Module.GetHttpManager();

	UWebApiResponseBodyString* ResponseBodyString = NewObject<UWebApiResponseBodyString>(GetTransientPackage(), UWebApiResponseBodyString::StaticClass());
	UWebApiResponseBodyBase* ResponseBody = (UWebApiResponseBodyBase*)ResponseBodyString;

	if(Response.IsValid())
	{
		ResponseBodyString->Code = Response->GetResponseCode();
		ResponseBodyString->SetResponse(bSuccessed ? Response->GetContentAsString() : TEXT("Request failed."));

		UE_LOG(LogTemp, Log, TEXT("Code : %d"), ResponseBodyString->Code);
		UE_LOG(LogTemp, Log, TEXT("Response : %s"), *ResponseBodyString->GetResponse());
	}
	else
	{
		ResponseBodyString->Code = 400;
		ResponseBodyString->SetResponse(TEXT("Request failed."));
	}

	while (PostFilters.IsEmpty() == false)
	{
		UObject* PostFilter = nullptr;
		if(PostFilters.Dequeue(PostFilter))
		{
			ResponseBody = IWebApiPostFilterInterface::Execute_ExecuteWebApiPostFilter(PostFilter, ResponseBody);
			if( ResponseBody == nullptr )
			{
				UE_LOG(LogTemp, Error, TEXT("ResponseBody is null."));
			}
		}
	}

	if(bSuccessed && ResponseBody != nullptr && SuccessResponseCodes.Find(ResponseBody->Code) >= 0)
	{
		OnRequestSuccessed.Broadcast(this, ResponseBody);
	}
	else
	{
		OnRequestFailed.Broadcast(this, ResponseBody);
	}

	OnRequestCompleted.Broadcast(this, ResponseBody);

	Manager.RemoveRequest(Request.ToSharedRef());

	bProcessing = false;
}

void UWebApi::OnRequestProgressInternal(FHttpRequestPtr Request, int32 Sent, int32 Received)
{
	OnRequestProgress.Broadcast(this, Sent, Received);
}
