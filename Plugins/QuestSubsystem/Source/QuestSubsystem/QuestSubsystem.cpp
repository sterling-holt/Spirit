// Copyright Epic Games, Inc. All Rights Reserved.

#include "QuestSubsystem.h"

#define LOCTEXT_NAMESPACE "FQuestSubsystemModule"

DEFINE_LOG_CATEGORY(LogQuestSubsystem);

void FQuestSubsystemModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	UE_LOG(LogQuestSubsystem, Warning, TEXT("Quest Subsystem module starting up"))
}

void FQuestSubsystemModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FQuestSubsystemModule, QuestSubsystem)