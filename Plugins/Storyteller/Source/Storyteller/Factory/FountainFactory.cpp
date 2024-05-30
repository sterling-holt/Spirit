#include "FountainFactory.h"
#include "../StoryAsset.h"
#include "../Editor/StorytellerEditor.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Toolkits/ToolkitManager.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"

UFountainFactory::UFountainFactory()
{
    bCreateNew = false;
    bEditAfterNew = true;
    bEditorImport = true;

    SupportedClass = UStoryAsset::StaticClass();
    Formats.Add(TEXT("fountain;Fountain Script"));
}

UObject* UFountainFactory::FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
    UStoryAsset* NewStoryAsset = NewObject<UStoryAsset>(InParent, InClass, InName, Flags);
    if (NewStoryAsset->LoadFountainStory(Filename))
    {
        // Open the asset in the custom editor after creation
        FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools");
        TArray<UObject*> ObjectsToEdit;
        ObjectsToEdit.Add(NewStoryAsset);

        // Open the custom editor
        TSharedRef<FStorytellerEditor> Editor = MakeShared<FStorytellerEditor>();
        Editor->InitToolkit(EToolkitMode::Standalone, TSharedPtr<IToolkitHost>(), NewStoryAsset);
        
        return NewStoryAsset;
    }

    bOutOperationCanceled = true;
    return nullptr;
}
