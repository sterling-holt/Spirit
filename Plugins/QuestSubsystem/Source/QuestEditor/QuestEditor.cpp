/**
*   Quest Editor
*   Docs: [...]
*   
* */



#include "QuestEditor.h"
#include "QuestSettings.h"
#include "ISettingsModule.h"
//  #include "LevelEditor.h"
//  #include "Framework/MultiBox/MultiBoxBuilder.h"
//  #include "SlateBasics.h"
//  #include "SlateExtras.h"


void FQuestEditorModule::StartupModule()
{
    if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
    {
        SettingsModule->RegisterSettings("Project", "Spirit", "Quest System",
            NSLOCTEXT("QuestSettings", "QuestConfigName", "Quest System"),
            NSLOCTEXT("QuestSettings", "QuestConfigDescription", "Configure the database settings for the Quest Editor."),
            GetMutableDefault<UQuestSettings>());
    }
}

void FQuestEditorModule::ShutdownModule()
{
    // Clean up module resources
    if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
    {
        SettingsModule->UnregisterSettings("Project", "Spirit", "Quest System");
    }
}

IMPLEMENT_MODULE(FQuestEditorModule, QuestEditor)


/*
void FQuestEditorModule::AddMenuExtension(FMenuBuilder& Builder)
{
    Builder.AddMenuEntry(
        FText::FromString("Open Quest Editor"),
        FText::FromString("Open the custom quest editor"),
        FSlateIcon(),
        FUIAction(FExecuteAction::CreateRaw(this, &FQuestEditorModule::OpenQuestEditor))
    );
}

void FQuestEditorModule::OpenQuestEditor()
{
    // Code to open your custom quest editor window
}
*/