// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "QuestSettings.generated.h"

/**
 * 
 */

UCLASS(config = Game, defaultconfig)
class QUESTEDITOR_API UQuestSettings : public UDeveloperSettings
{
    GENERATED_BODY()

public:
    UQuestSettings();
    // Add your database configuration keys here
    UPROPERTY(config, EditAnywhere, Category = "Database Configuration")
    FString DatabaseIP;

    UPROPERTY(config, EditAnywhere, Category = "Database Configuration")
    int32 DatabasePort;

    UPROPERTY(config, EditAnywhere, Category = "Database Configuration")
    FString DatabaseUser;

    UPROPERTY(config, EditAnywhere, Category = "Database Configuration")
    FString DatabasePassword;

    // Add more configuration keys as needed
};
