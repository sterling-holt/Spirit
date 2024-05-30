#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"
#include "../StoryAsset.h"
#include "../Storyteller.h"

class STORYTELLER_API FAssetTypeActions_StoryAsset : public FAssetTypeActions_Base
{
public:
    // IAssetTypeActions implementation
    virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_ScriptAsset", "Story Asset"); }
    virtual FColor GetTypeColor() const override { return FColor::Green; }
    virtual UClass* GetSupportedClass() const override { return UStoryAsset::StaticClass(); }
    virtual uint32 GetCategories() override { return EAssetTypeCategories::Misc; }

    // Implement OpenAsset for custom editor
    virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor) override;
};
