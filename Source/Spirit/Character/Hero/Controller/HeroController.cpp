// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include <Spirit/UI/Subsystem/UISubsystem.h>
//  #include "StarfallHeroCharacter.h"

AHeroController::AHeroController()
{
    UE_LOG(LogTemp, Display, TEXT("Player controller stuff"));
    bReplicates = true;
}



void AHeroController::BeginPlay()
{
    Super::BeginPlay();
    OnControllerReady.Broadcast();

    UGameInstance* GameInstance = GetGameInstance();
    if (GameInstance != nullptr)
    {
        // Replace 'YourUserInterfaceSubsystem' with the actual name of your subsystem class
        // And replace 'GetSubsystem<YourUserInterfaceSubsystem>()' with the correct method to get your subsystem
        UUISubsystem* UISubsystem = GameInstance->GetSubsystem<UUISubsystem>();
        if (UISubsystem != nullptr)
        {
            UISubsystem->Display(this);
        }
    }


    if (GetLocalPlayer())
    {
        EnhancedInputSubsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
        if (EnhancedInputSubsystem) {
            //  if (UIContext != nullptr) { SwitchInputContext(UIContext, 0); }
    
            //  AStarfallCharacter* StarfallCharacter = Cast<AStarfallCharacter>(GetPawn());
            //  if (StarfallCharacter)
            //  {
            //      UE_LOG(LogTemp, Warning, TEXT("Testing character?"))
            //          StarfallCharacter->OnPawnPossessed.AddDynamic(this, &AStarfallHeroController::HandlePawnPossessed);
            //      StarfallCharacter->OnPawnUnPossessed.AddDynamic(this, &AStarfallHeroController::HandlePawnUnPossessed);
            //  }
        }
        else {
            UE_LOG(LogTemp, Warning, TEXT("Subsystem not found."));
        }
    }
}

void AHeroController::SetupInputComponent()
{
    Super::SetupInputComponent();
    EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
    if (EnhancedInputComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("Setting up enhanced input in player controller"))
    }
}



void AHeroController::SwitchInputContext(UInputMappingContext* NewContext, int32 Priority)
{
    if (GetLocalPlayer())
    {
        EnhancedInputSubsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
        if (EnhancedInputSubsystem)
        {
            UE_LOG(LogTemp, Warning, TEXT("Clearing out mappings and setting new context"));
            // Clear the current context to avoid overlaps
            EnhancedInputSubsystem->ClearAllMappings();
        
            // Add the new context with the specified priority
            EnhancedInputSubsystem->AddMappingContext(NewContext, Priority);
        }
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("No subsystem found :("))
    }
}




/*

void AStarfallHeroController::HandlePawnPossessed()
{
    //  UE_LOG(LogTemp, Warning, TEXT("possess from controller???"))

    //  this may be removed, we shouldn't need to do anything after possession? unless we want to do something with nakama!
}


void AStarfallHeroController::HandlePawnUnPossessed()
{
    UE_LOG(LogTemp, Warning, TEXT("Unpossessed from controller???"))

    //  SwitchInputContext(UIContext, 0);
}

*/