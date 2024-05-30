#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"
#include "ScriptAsset.h"

class STORYGRAPHEDITOR_API FAssetTypeActions_ScriptAsset : public FAssetTypeActions_Base
{
public:
    // IAssetTypeActions implementation
    virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_ScriptAsset", "Script Asset"); }
    virtual FColor GetTypeColor() const override { return FColor::Green; }
    virtual UClass* GetSupportedClass() const override { return UScriptAsset::StaticClass(); }
    virtual uint32 GetCategories() override { return EAssetTypeCategories::Misc; }
};
