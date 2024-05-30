#include "ScriptAsset.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

UScriptAsset::UScriptAsset()
{
    // Initialize any necessary properties here
}

bool UScriptAsset::LoadFountainScript(const FString& FilePath)
{
    FString FileContent;
    if (FFileHelper::LoadFileToString(FileContent, *FilePath))
    {
        TArray<FString> Lines;
        FileContent.ParseIntoArrayLines(Lines);

        for (const FString& Line : Lines)
        {
            ParseFountainLine(Line);
        }

        return true;
    }

    return false;
}

void UScriptAsset::ParseFountainLine(const FString& Line)
{
    // Simplified parsing logic for dialogue lines
    if (Line.StartsWith("  ")) // Dialogue lines typically start with two spaces
    {
        FString Dialogue = Line.TrimStart();
        if (Dialogue.IsEmpty())
        {
            return;
        }

        if (Dialogues.Num() > 0 && !Dialogues.Last().Dialogue.IsEmpty())
        {
            Dialogues.Last().Dialogue += TEXT(" ") + Dialogue;
        }
        else
        {
            FDialogue NewLine;
            NewLine.Dialogue = Dialogue;
            Dialogues.Add(NewLine);
        }
    }
    else if (Line.EndsWith(":")) // Character names typically end with a colon
    {
        FDialogue NewLine;
        NewLine.ActorID = Line.LeftChop(1).TrimStart();
        Dialogues.Add(NewLine);
    }
}
