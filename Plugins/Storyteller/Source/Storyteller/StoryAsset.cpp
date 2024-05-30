
#include "StoryAsset.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

UStoryAsset::UStoryAsset()
{
    // Initialize any necessary properties here
}

bool UStoryAsset::LoadFountainStory(const FString& FilePath)
{
    TArray<FString> FileLines;
    if (FFileHelper::LoadFileToStringArray(FileLines, *FilePath))
    {
        for (const FString& Line : FileLines)
        {
            ParseFountainLine(Line);
        }
        return true;
    }
    return false;
}

void UStoryAsset::ParseFountainLine(const FString& Line)
{
    // Simple example of parsing logic
    // Real implementation would involve more comprehensive parsing

    if (Line.StartsWith("INT.") || Line.StartsWith("EXT."))
    {
        // Handle scene heading
    }
    else if (Line.IsEmpty())
    {
        // Handle empty lines
    }
    else if (Line.Contains(":"))
    {
        // Handle dialogue
        FString Character, Dialogue;
        Line.Split(TEXT(":"), &Character, &Dialogue);
        DialogueLines.Add(FDialogueLine{ Character.TrimStartAndEnd(), Dialogue.TrimStartAndEnd() });
    }
    else
    {
        // Handle stage directions
        StageDirections.Add(FStageDirection{ Line });
    }
}
