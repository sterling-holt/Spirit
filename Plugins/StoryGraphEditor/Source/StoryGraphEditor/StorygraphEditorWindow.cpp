// SStorygraphEditorWindow.cpp
#include "StorygraphEditorWindow.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SGridPanel.h"

void SStorygraphEditorWindow::Construct(const FArguments& InArgs)
{
    ChildSlot
    [
        SNew(SVerticalBox)
        + SVerticalBox::Slot()
        .AutoHeight()
        [
            SNew(SGridPanel)
            + SGridPanel::Slot(0, 0)
            [
                SNew(SBorder)
                .Content()
                [
                    SNew(STextBlock).Text(FText::FromString("Camera Setup"))
                ]
            ]
            + SGridPanel::Slot(1, 0)
            [
                SNew(SBorder)
                .Content()
                [
                    SNew(STextBlock).Text(FText::FromString("Active Camera View"))
                ]
            ]
            + SGridPanel::Slot(2, 0)
            [
                SNew(SBorder)
                .Content()
                [
                    SNew(STextBlock).Text(FText::FromString("Script"))
                ]
            ]
        ]
        + SVerticalBox::Slot()
        .FillHeight(1.0)
        [
            SNew(SBorder)
            .Content()
            [
                SNew(STextBlock).Text(FText::FromString("Custom Sequencer Placeholder"))
            ]
        ]
    ];
}
