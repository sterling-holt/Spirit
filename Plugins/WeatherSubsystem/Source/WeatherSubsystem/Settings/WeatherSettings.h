// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "WeatherSettings.generated.h"

/*	-------------------------------------------------
 * 
 * 
 * 
 * 
 * 
	------------------------------------------------- */

USTRUCT(BlueprintType)
struct FSeasonConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Seasons")
	FString SeasonName;

	UPROPERTY(EditAnywhere, Category = "Seasons")
	bool bEnabled;
};


UCLASS(config = Game, defaultconfig)
class WEATHERSUBSYSTEM_API UWeatherSettings : public UDeveloperSettings
{
	GENERATED_BODY()


protected:


public:
	UWeatherSettings();

	// Map to store season configurations
	UPROPERTY(config, EditAnywhere, Category = "Seasons")
	TArray<FSeasonConfig> Seasons;
	
};
