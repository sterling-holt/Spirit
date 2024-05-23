// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
//  #include "StarfallHeroCharacter.h"

AHeroController::AHeroController()
{
    UE_LOG(LogTemp, Display, TEXT("Player controller stuff"));
    bReplicates = true;
}



void AHeroController::BeginPlay()
{
    Super::BeginPlay();
    //  OnControllerReady.Broadcast();
    //  UE_LOG(LogTemp, Warning, TEXT("Controller available"))
    //  
    //      UISubsystem = GetGameInstance()->GetSubsystem<UUserInterfaceSubsystem>();
    //  if (UISubsystem)
    //  {
    //      UIWidget = UISubsystem->Mount();
    //      //  UIWidget->AddToViewport();
    //      UE_LOG(LogTemp, Warning, TEXT("UI Widget created and added to viewport"))
    //  }
    //  
    //  //  ----
    //  
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