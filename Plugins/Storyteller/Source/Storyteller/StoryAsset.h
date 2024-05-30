
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StoryAsset.generated.h"

// Struct to hold dialogue lines
USTRUCT(BlueprintType)
struct FDialogueLine
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    FString Character;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    FString Dialogue;
};

// Struct to hold stage directions
USTRUCT(BlueprintType)
struct FStageDirection
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageDirection")
    FString Description;
};

// Story asset class
UCLASS(BlueprintType, Blueprintable)
class STORYTELLER_API UStoryAsset : public UObject
{
    GENERATED_BODY()

public:
    UStoryAsset();

    // Array to hold all dialogue lines
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Script")
    TArray<FDialogueLine> DialogueLines;

    // Array to hold all stage directions
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Script")
    TArray<FStageDirection> StageDirections;

    // Function to load and parse a Fountain script
    UFUNCTION(BlueprintCallable, Category = "Script")
    bool LoadFountainStory(const FString& FilePath);

private:
    void ParseFountainLine(const FString& Line);
};
