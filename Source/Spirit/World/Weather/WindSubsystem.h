// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "WindSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class SPIRIT_API UWindSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	UWindSubsystem();

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Wind")
    FVector WindDirection;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Wind")
    float WindSpeed;

    void UpdateWind(FVector NewDirection, float NewSpeed);
};
