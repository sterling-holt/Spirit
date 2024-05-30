#include "StorytellerEditor.h"
#include "Widgets/Layout/SSplitter.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SBox.h"
#include "Toolkits/ToolkitManager.h"
#include "Widgets/Docking/SDockTab.h"

#define LOCTEXT_NAMESPACE "FStorytellerEditor"

void FStorytellerEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
    WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_CustomAssetEditor", "Storyteller Editor"));
    auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

    InTabManager->RegisterTabSpawner("StorytellerEditorTab", FOnSpawnTab::CreateSP(this, &FStorytellerEditor::SpawnTab))
        .SetDisplayName(LOCTEXT("StorytellerEditorTab", "Storyteller Editor"))
        .SetGroup(WorkspaceMenuCategoryRef);
}

void FStorytellerEditor::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
    InTabManager->UnregisterTabSpawner("StorytellerEditorTab");
}

FName FStorytellerEditor::GetToolkitFName() const { return FName("StorytellerEditor"); }
FText FStorytellerEditor::GetBaseToolkitName() const { return LOCTEXT("AppLabel", "Storyteller Editor"); }
FString FStorytellerEditor::GetWorldCentricTabPrefix() const { return LOCTEXT("WorldCentricTabPrefix", "Storyteller ").ToString(); }
FLinearColor FStorytellerEditor::GetWorldCentricTabColorScale() const { return FLinearColor::White; }

void FStorytellerEditor::InitToolkit(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* ObjectToEdit)
{
    EditingObject = ObjectToEdit;
    const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("Standalone_StorytellerEditor_Layout")
        ->AddArea
        (
            FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
            ->Split
            (
                FTabManager::NewStack()
                ->AddTab("StorytellerEditorTab", ETabState::OpenedTab)
                ->SetForegroundTab(FTabId("StorytellerEditorTab"))
            )
        );

    InitAssetEditor(Mode, InitToolkitHost, "StorytellerEditor", StandaloneDefaultLayout, true, true, ObjectToEdit);
}

TSharedRef<SDockTab> FStorytellerEditor::SpawnTab(const FSpawnTabArgs& Args)
{
    return SNew(SDockTab)
        .TabRole(ETabRole::PanelTab)
        [
            SNew(SSplitter)
                .Orientation(Orient_Vertical)
                + SSplitter::Slot()
                .Value(0.7f)
                [
                    SNew(SSplitter)
                        .Orientation(Orient_Horizontal)
                        + SSplitter::Slot()
                        .Value(0.33f)
                        [
                            // Widget for scene/camera placement
                            SNew(STextBlock).Text(LOCTEXT("SceneCameraText", "Scene/Camera Placement View"))
                        ]
                        + SSplitter::Slot()
                        .Value(0.33f)
                        [
                            // Widget for active camera view
                            SNew(STextBlock).Text(LOCTEXT("ActiveCameraText", "Active Camera View"))
                        ]
                        + SSplitter::Slot()
                        .Value(0.33f)
                        [
                            // Widget for script view
                            SNew(STextBlock).Text(LOCTEXT("ScriptText", "Script View"))
                        ]
                ]
                + SSplitter::Slot()
                .Value(0.3f)
                [
                    // Widget for sequence editor
                    SNew(STextBlock).Text(LOCTEXT("SequencerText", "Sequence Editor"))
                ]
        ];
}

#undef LOCTEXT_NAMESPACE
