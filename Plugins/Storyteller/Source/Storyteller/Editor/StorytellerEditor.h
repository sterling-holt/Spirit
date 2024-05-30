#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"

class STORYTELLER_API FStorytellerEditor : public FAssetEditorToolkit
{
public:
    virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
    virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

    virtual FName GetToolkitFName() const override;
    virtual FText GetBaseToolkitName() const override;
    virtual FString GetWorldCentricTabPrefix() const override;
    virtual FLinearColor GetWorldCentricTabColorScale() const override;

    void InitToolkit(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* ObjectToEdit);

private:
    TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& Args); // Added function declaration
    UObject* EditingObject;
};




/*
#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"

class STORYTELLER_API FStorytellerEditor : public FAssetEditorToolkit
{
public:
    virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
    virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

    virtual FName GetToolkitFName() const override;
    virtual FText GetBaseToolkitName() const override;
    virtual FString GetWorldCentricTabPrefix() const override;
    virtual FLinearColor GetWorldCentricTabColorScale() const override;

    void InitToolkit(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* ObjectToEdit);

private:
    TSharedRef<SDockTab> SpawnTab_SceneCamera(const FSpawnTabArgs& Args);
    TSharedRef<SDockTab> SpawnTab_ActiveCamera(const FSpawnTabArgs& Args);
    TSharedRef<SDockTab> SpawnTab_Script(const FSpawnTabArgs& Args);

    UObject* EditingObject;
};

*/