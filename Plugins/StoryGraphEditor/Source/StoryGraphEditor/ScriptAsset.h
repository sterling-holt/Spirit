#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ScriptAsset.generated.h"

// Struct to hold a single line of dialogue for an actor
USTRUCT(BlueprintType)
struct FDialogue
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    FString ActorID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    FString Dialogue;
};

// Script asset class
UCLASS(BlueprintType, Blueprintable)
class STORYGRAPHEDITOR_API UScriptAsset : public UObject
{
    GENERATED_BODY()

public:
    UScriptAsset();

    // Array to hold all dialogue lines
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Script")
    TArray<FDialogue> Dialogues;

    // Function to load and parse a Fountain script
    UFUNCTION(BlueprintCallable, Category = "Script")
    bool LoadFountainScript(const FString& FilePath);

private:
    void ParseFountainLine(const FString& Line);
};
