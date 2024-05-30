// Copyright Epic Games, Inc. All Rights Reserved.

#include "Storyteller.h"
#include "Modules/ModuleManager.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "Factory/AssetTypeActions_StoryAsset.h"
#include "StoryAsset.h"

#define LOCTEXT_NAMESPACE "FStorytellerModule"

void FStorytellerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
    StoryAssetTypeActions = MakeShareable(new FAssetTypeActions_StoryAsset);
    AssetTools.RegisterAssetTypeActions(StoryAssetTypeActions.ToSharedRef());
}

void FStorytellerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
    {
        IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
        AssetTools.UnregisterAssetTypeActions(StoryAssetTypeActions.ToSharedRef());
    }
    StoryAssetTypeActions.Reset();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FStorytellerModule, Storyteller)