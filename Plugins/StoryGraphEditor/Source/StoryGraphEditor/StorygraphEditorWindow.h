#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

class SStorygraphEditorWindow : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SStorygraphEditorWindow) {}
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);
};