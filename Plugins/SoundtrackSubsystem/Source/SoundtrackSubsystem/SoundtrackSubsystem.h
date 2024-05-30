// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ISettingsModule.h"
#include "Modules/ModuleManager.h"



class FSoundtrackSubsystemModule : public IModuleInterface
{
public:

	ISettingsModule* SettingsModule;

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
