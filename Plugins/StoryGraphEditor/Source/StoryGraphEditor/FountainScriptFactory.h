
#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "FountainScriptFactory.generated.h"

UCLASS()
class STORYGRAPHEDITOR_API UFountainScriptFactory : public UFactory
{
    GENERATED_BODY()

public:
    UFountainScriptFactory();

    // Override factory functions
    virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;
};