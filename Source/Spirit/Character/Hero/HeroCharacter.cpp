// Fill out your copyright notice in the Description page of Project Settings.



#include "HeroCharacter.h"
#include "Controller/HeroController.h"
#include "Spirit/Character/GameplayAbilities/FireBlastAbility.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <GameplayAbilitySpec.h>
#include <Spirit/Character/GameplayAbilities/ProjectileAbility.h>

AHeroCharacter::AHeroCharacter()
{
	UE_LOG(LogTemp, Warning, TEXT("Hero Character!"))







	GetCharacterMovement()->bOrientRotationToMovement = false; // Character moves in the direction of input...
	bUseControllerRotationPitch =	false;
	bUseControllerRotationYaw =     true;
	bUseControllerRotationRoll =	false;
}



void AHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (AbilitySystemComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ability System loaded!"))
			//	Example of granting an ability to the cha	racter
			//	Replace `UGameplayAbility` with your specific ability class
			//	AbilitySystemComponent->InitAbilityActorInfo(this, this);
			//	AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(UFireBlastAbility::StaticClass(), 1, 0));
			//	FGameplayAbilitySpec AbilitySpec(UFireBlastAbility::StaticClass(), 1, 0);
			//	AbilitySystemComponent->GiveAbility(AbilitySpec);
			//	
			//	// Retrieve the instance of FireBlastAbility
			//	for (const FGameplayAbilitySpec& Spec : AbilitySystemComponent->GetActivatableAbilities())
			//	{
			//		if (Spec.Ability && Spec.Ability->GetClass() == UProjectileAbility::StaticClass())
			//		{
			//			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(UProjectileAbility::StaticClass(), 1, 0, this));
			//			ProjectileAbility = Cast<UProjectileAbility>(Spec.Ability);
			//			break;
			//		}
			//	}


			this->GrantAbility(UProjectileAbility::StaticClass(), 1, 0);
	}
}



void AHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	UE_LOG(LogTemp, Warning, TEXT("Possessed log from Hero Character!"))

	// We'll send our Input Context and Actions to controller here!
	AHeroController* HeroController = Cast<AHeroController>(NewController);
	if (HeroController)
	{
		UEnhancedInputComponent* EnhancedInputComponent = HeroController->GetEnhancedInputComponent();
		if (EnhancedInputComponent)
		{
			UE_LOG(LogTemp, Warning, TEXT("Enhanced Input confirmed"))
				//	Setup the context
				//	UInputMappingContext* MyInputContext = CreateInputContext(); // You need to implement this
				HeroController->SwitchInputContext(PawnInputContext, 0); // Assumes priority 1

			//	Bind actions
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHeroCharacter::IA_Look);
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHeroCharacter::IA_Move);

			EnhancedInputComponent->BindAction(GAS_FireBlast, ETriggerEvent::Triggered, this, &AHeroCharacter::IA_FireBlast);

			//	----
			//	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AHeroCharacter::Jump);
			//	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AHeroCharacter::StopJumping);

			//	----
			//	EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AHeroCharacter::Crouch);
			//	EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AHeroCharacter::UnCrouch);

			//	----
			//	EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AStarfallHeroCharacter::Sprint);
			//	EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AStarfallHeroCharacter::StopSprinting);
		}
		else {
			UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
		}
	}
}



void AHeroCharacter::IA_Look(const FInputActionValue& Value)
{
	//	UE_LOG(LogTemp, Warning, TEXT("Looking"))
	//	input is a Vector2D
	FVector2D _Value = Value.Get<FVector2D>();
	this->Look(_Value);
}



void AHeroCharacter::IA_Move(const FInputActionValue& Value)
{
	//	UE_LOG(LogTemp, Warning, TEXT("Moving"))

	//	input is a Vector2D
	FVector2D _Value = Value.Get<FVector2D>();
	this->Move(_Value);
}



void AHeroCharacter::IA_FireBlast()
{

	//	UE_LOG(LogTemp, Warning, TEXT("Fire Blast!?"))
	if (AbilitySystemComponent)
	{
		//	UE_LOG(LogTemp, Warning, TEXT("Ability Component found"))
		AbilitySystemComponent->TryActivateAbilityByClass(UProjectileAbility::StaticClass());
	}
}


void AHeroCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AHeroCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}