// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameplayTagContainer.h"
#include "ElementParticle.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class ELEMENTMANIPULATION_API UElementParticle : public UParticleSystemComponent
{
	GENERATED_BODY()
	
public:
	UElementParticle();

	// Gameplay tags associated with this particle system
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	FGameplayTagContainer GameplayTags;
};
