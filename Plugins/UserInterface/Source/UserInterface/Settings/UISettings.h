// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "CommonACtivatableWidget.h"
#include "Engine/DeveloperSettings.h"
#include "UISettings.generated.h"

/**
 * 
 */
UCLASS(config = Game, defaultconfig)
class USERINTERFACE_API UUISettings : public UDeveloperSettings
{
	GENERATED_BODY()
	

public:
	UUISettings();


	//	Add your UI configuration keys here
	//	UPROPERTY(config, EditAnywhere, Category = "UI Window")
	//	TSoftObjectPtr<UCommonUserWidget> Window;	//	This will probably just be defined as a C++ CommonUserWidget.

	UPROPERTY(config, EditAnywhere, Category = "UI Screens")
	TSoftClassPtr<UCommonActivatableWidget> Startup;

	//	UPROPERTY(config, EditAnywhere, Category = "UI Screens")
	//	TSoftClassPtr<AGameStateBase> GameState;

	//	UPROPERTY(config, EditAnywhere, Category = "UI Screens")
	//	TSoftClassPtr<APlayerState> UIPlayerState;

	//	UPROPERTY(config, EditAnywhere, Category = "UI Screens")
	//	TSoftObjectPtr<TSubclassOf<UCommonActivatableWidget>> Lobby;
};
