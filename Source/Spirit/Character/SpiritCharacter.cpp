// Copyright Epic Games, Inc. All Rights Reserved.

#include "SpiritCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include <GameplayAbilitySpec.h>
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameplayAbilities/BenderAbilitySystemComponent.h"


//////////////////////////////////////////////////////////////////////////
// ASpiritCharacter

ASpiritCharacter::ASpiritCharacter()
{
	// Create the Ability System Component and attach it to the character
	AbilitySystemComponent = CreateDefaultSubobject<UBenderAbilitySystemComponent>(TEXT("AbilitySystemComponent"));


	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;



	// Create a camera boom (pulls in towards the player if there is a collision)
	Boom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	Boom->SetupAttachment(RootComponent);
	Boom->TargetArmLength = 125.0f; // The camera follows at this distance behind the character	
	Boom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	Boom->SetRelativeLocation(FVector(0.f, 0.f, 128.f));

	//	Create a follow camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	Camera->SetupAttachment(Boom); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	Camera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm




	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ASpiritCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

//	void ASpiritCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//	{
//		// Add Input Mapping Context
//		if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
//		{
//			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
//			{
//				Subsystem->AddMappingContext(DefaultMappingContext, 0);
//			}
//		}
//		
//		// Set up action bindings
//		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
//			
//			// Jumping
//			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
//			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
//	
//			// Moving
//			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASpiritCharacter::Move);
//	
//			// Looking
//			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASpiritCharacter::Look);
//		}
//		else
//		{
//			UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
//		}
//	}




/*
*/
void ASpiritCharacter::Move(FVector2D Value)
{
	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Value.Y);
		AddMovementInput(RightDirection, Value.X);
	}
}

void ASpiritCharacter::Look(FVector2D Value)
{


	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Value.X);
		AddControllerPitchInput(Value.Y);
	}
}





void ASpiritCharacter::GrantAbility(TSubclassOf<UGameplayAbility> Ability, int32 Level, int32 InputID)
{
	if (!AbilitySystemComponent || !Ability)
	{
		UE_LOG(LogTemp, Warning, TEXT("AbilitySystemComponent or Ability is null"));
		return;
	}

	FGameplayAbilitySpec AbilitySpec(Ability, Level, InputID, this);
	AbilitySystemComponent->GiveAbility(AbilitySpec);
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	UE_LOG(LogTemp, Warning, TEXT("Granted Ability: %s"), *Ability->GetName());
}