#include "WebApiModule.h"

#define LOCTEXT_NAMESPACE "FWebApiModule"

DEFINE_LOG_CATEGORY(LogWebApi);

void FWebApiModule::StartupModule()
{
}

void FWebApiModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FWebApiModule, WebApi)
