// Copyright Epic Games, Inc. All Rights Reserved.

#include "UserInterface.h"
#include <ISettingsModule.h>
#include "Settings/UISettings.h"
#include "Subsystem/UserInterfaceSubsystem.h"
#include <Kismet/GameplayStatics.h>
#include "GameplayTagsManager.h"
#include <GameFramework/PlayerState.h>

#define LOCTEXT_NAMESPACE "FUserInterfaceModule"






void FUserInterfaceModule::StartupModule()
{
    UE_LOG(LogTemp, Warning, TEXT("FUserInterfaceModule::StartupModule() called."));

    if (!SettingsModule) {
        SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
        if (SettingsModule)
        {
            SettingsModule->RegisterSettings("Project", "Spirit", "UserInterface",
                NSLOCTEXT("UIProjectSettings", "UIConfigName", "User Interface"),
                NSLOCTEXT("UIProjectSettings", "UIConfigDescription", "Configure the UI settings for the project."),
                GetMutableDefault<UUISettings>());
        }
    }

    // Register the tag table file for the plugin
    UGameplayTagsManager& TagsManager = UGameplayTagsManager::Get();
    TagsManager.AddTagIniSearchPath(FPaths::Combine(FPaths::ProjectPluginsDir(), TEXT("YourPlugin/Config/UI_Tags.ini")));


}

void FUserInterfaceModule::ShutdownModule()
{
    if (SettingsModule)
    {
        SettingsModule->UnregisterSettings("Project", "Spirit", "User Interface");
    }
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUserInterfaceModule, UserInterface)