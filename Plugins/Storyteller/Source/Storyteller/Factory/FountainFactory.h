
#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "../StoryAsset.h"
#include "FountainFactory.generated.h"

UCLASS()
class STORYTELLER_API UFountainFactory : public UFactory
{
    GENERATED_BODY()

public:
    UFountainFactory();

    // Override factory functions
    virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;
};
