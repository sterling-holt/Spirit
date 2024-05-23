// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayAbilities/BenderAbilitySystemComponent.h"
#include "SpiritCharacter.generated.h"


UCLASS(config=Game)
class ASpiritCharacter : public ACharacter
{
	GENERATED_BODY()



public:
	ASpiritCharacter();
	
	// Ability System Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	UBenderAbilitySystemComponent* AbilitySystemComponent;

protected:

	/** Called for movement input */
	void Move(FVector2D Value);

	/** Called for looking input */
	void Look(FVector2D Value);
			

protected:
	//	APawn interface
	//	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();



	void GrantAbility(TSubclassOf<UGameplayAbility> Ability, int32 Level, int32 InputID);
};

