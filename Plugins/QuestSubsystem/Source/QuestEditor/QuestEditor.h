
#pragma once

#include "Modules/ModuleManager.h"

class FQuestEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
    //  void AddMenuExtension(FMenuBuilder& Builder);
    //  void OpenQuestEditor();
};

