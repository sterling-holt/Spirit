#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "IAssetTypeActions.h" // Correct header to include IAssetTypeActions

class FStorytellerModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
    TSharedPtr<IAssetTypeActions> StoryAssetTypeActions; // Correct usage of TSharedPtr
};
