// Copyright Epic Games, Inc. All Rights Reserved.

#include "WeatherSubsystem.h"
#include "Settings/WeatherSettings.h"

#define LOCTEXT_NAMESPACE "FWeatherSubsystemModule"

void FWeatherSubsystemModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
    SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
    if (SettingsModule)
    {
        SettingsModule->RegisterSettings("Project", "Spirit", "Weather Subsystem",
            NSLOCTEXT("QuestSettings", "QuestConfigName", "Weather Subsystem"),
            NSLOCTEXT("QuestSettings", "QuestConfigDescription", "Configure Weather subsystem"),
            GetMutableDefault<UWeatherSettings>());
    }
}

void FWeatherSubsystemModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

    if (SettingsModule)
    {
        SettingsModule->UnregisterSettings("Project", "Project", "User Interface");
    }
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FWeatherSubsystemModule, WeatherSubsystem)