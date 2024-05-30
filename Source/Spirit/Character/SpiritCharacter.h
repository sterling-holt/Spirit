// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../../../../../../../Program Files/Epic Games/UE_5.4/Engine/Plugins/Experimental/Animation/MotionTrajectory/Source/MotionTrajectory/Public/CharacterTrajectoryComponent.h"
#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "SpiritCharacter.generated.h"



//	POSSESSION	-----
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPawnPossessedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPawnUnPossessedDelegate);



class USpringArmComponent;
class UCameraComponent;

UCLASS(config=Game)
class ASpiritCharacter : public ACharacter
{
	GENERATED_BODY()




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
	virtual void UnPossessed() override;
	virtual void PossessedBy(AController* NewController) override;



	void GrantAbility(TSubclassOf<UGameplayAbility> Ability, int32 Level, int32 InputID);





public:
	ASpiritCharacter();

	// Ability System Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	//	UBenderAbilitySystemComponent* AbilitySystemComponent;
	UAbilitySystemComponent* AbilitySystemComponent;
	




	FOnPawnPossessedDelegate OnPawnPossessed;
	FOnPawnUnPossessedDelegate OnPawnUnPossessed;



	
	
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* Boom;
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return Boom; }

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return Camera; }



	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Default")
	TObjectPtr<UCharacterTrajectoryComponent> CharacterTrajectory;
	//	TObjectPtr<USpiritTrajectory> CharacterTrajectory;

};

