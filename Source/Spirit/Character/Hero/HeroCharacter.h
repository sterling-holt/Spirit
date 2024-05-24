// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
//	#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Spirit/Character/SpiritCharacter.h"
#include "HeroCharacter.generated.h"


class UInputMappingContext;
class UInputAction;
struct FInputActionValue;





UCLASS()
class SPIRIT_API AHeroCharacter : public ASpiritCharacter
{
	GENERATED_BODY()
	

protected:
	virtual void PossessedBy(AController* NewController) override;

	virtual void BeginPlay() override;





public:
	AHeroCharacter();

	//  ------------------------------------------------------------






	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* CrouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* GAS_FireBlast;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* PawnInputContext;


	UProjectileAbility* ProjectileAbility;


	UFUNCTION(BlueprintCallable)
	UProjectileAbility* GetProjectileAbility() const { return ProjectileAbility; };


	//  ------------------------------------------------------------



	virtual void IA_Look(const FInputActionValue& Value);
	virtual void IA_Move(const FInputActionValue& Value);

	virtual void IA_FireBlast();


	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float BaseLookUpRate;



	UInputMappingContext* GetInputContext() const { return PawnInputContext; };
};