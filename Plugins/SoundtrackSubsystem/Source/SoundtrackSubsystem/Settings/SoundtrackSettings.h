// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "SoundtrackSettings.generated.h"

/**
 * 
 */

UCLASS(config = Game, defaultconfig)
class SOUNDTRACKSUBSYSTEM_API USoundtrackSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	USoundtrackSettings();

	// Add your UI configuration keys here
	UPROPERTY(config, EditAnywhere, Category = "UI Window")
	FString Window;	//	This will probably just be defined as a C++ CommonUserWidget.

};
