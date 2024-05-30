// Copyright Epic Games, Inc. All Rights Reserved.

#include "StoryGraphEditor.h"
#include "StorygraphEditorWindow.h"
#include <LevelEditor.h>
#include "AssetTypeActions_ScriptAsset.h"
#include "AssetToolsModule.h"
#include <IAssetTools.h>

#define LOCTEXT_NAMESPACE "FStoryGraphEditorModule"

const FName FStoryGraphEditorModule::StoryGraphEditorTabName(TEXT("StorygraphEditor"));


void FStoryGraphEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
    FGlobalTabmanager::Get()->RegisterNomadTabSpawner(StoryGraphEditorTabName, FOnSpawnTab::CreateRaw(this, &FStoryGraphEditorModule::OnSpawnPluginTab))
        .SetDisplayName(LOCTEXT("FStorygraphEditorTabTitle", "Storygraph Editor"))
        .SetMenuType(ETabSpawnerMenuType::Hidden);


    FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
    TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender);
    MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, nullptr, FMenuExtensionDelegate::CreateRaw(this, &FStoryGraphEditorModule::AddMenuExtension));

    LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);



    // Register the asset factory
    IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
    AssetTools.RegisterAssetTypeActions(MakeShareable(new FAssetTypeActions_ScriptAsset));
}


void FStoryGraphEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}


TSharedRef<SDockTab> FStoryGraphEditorModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
    return SNew(SDockTab)
        .TabRole(ETabRole::NomadTab)
        [
            SNew(SStorygraphEditorWindow)
        ];
}


void FStoryGraphEditorModule::AddMenuExtension(FMenuBuilder& Builder)
{
    Builder.AddMenuEntry(
        LOCTEXT("OpenStorygraphEditor", "Open Storygraph Editor"),
        LOCTEXT("OpenStorygraphEditorToolTip", "Open the custom storygraph editor window."),
        FSlateIcon(),
        FUIAction(FExecuteAction::CreateRaw(this, &FStoryGraphEditorModule::OpenStorygraphEditorWindow))
    );
}


void FStoryGraphEditorModule::OpenStorygraphEditorWindow()
{
    FGlobalTabmanager::Get()->TryInvokeTab(StoryGraphEditorTabName);
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FStoryGraphEditorModule, StoryGraphEditor)