#include "FountainScriptFactory.h"
#include "ScriptAsset.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

UFountainScriptFactory::UFountainScriptFactory()
{
    bCreateNew = false;
    bEditAfterNew = true;
    bEditorImport = true;

    SupportedClass = UScriptAsset::StaticClass();
    Formats.Add(TEXT("fountain;Fountain Script"));
}

UObject* UFountainScriptFactory::FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
    UScriptAsset* NewScriptAsset = NewObject<UScriptAsset>(InParent, InClass, InName, Flags);
    if (NewScriptAsset->LoadFountainScript(Filename))
    {
        return NewScriptAsset;
    }

    bOutOperationCanceled = true;
    return nullptr;
}
