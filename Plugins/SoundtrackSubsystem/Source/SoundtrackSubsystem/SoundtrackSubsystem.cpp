// Copyright Epic Games, Inc. All Rights Reserved.

#include "SoundtrackSubsystem.h"
#include <ISettingsModule.h>
#include "Settings/SoundtrackSettings.h"

#define LOCTEXT_NAMESPACE "FSoundtrackSubsystemModule"

void FSoundtrackSubsystemModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
    SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
    if (SettingsModule)
    {
        SettingsModule->RegisterSettings("Project", "Spirit", "Soundtrack",
            NSLOCTEXT("QuestSettings", "QuestConfigName", "Soundtrack"),
            NSLOCTEXT("QuestSettings", "QuestConfigDescription", "Configure the database settings for the soundtrack."),
            GetMutableDefault<USoundtrackSettings>());
    }
}

void FSoundtrackSubsystemModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
        // Clean up module resources
    if (SettingsModule)
    {
        SettingsModule->UnregisterSettings("Project", "Spirit", "Soundtrack");
    }
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSoundtrackSubsystemModule, SoundtrackSubsystem)