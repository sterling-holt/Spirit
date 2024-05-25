// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include <Spirit/UI/Subsystem/UISubsystem.h>
#include <Spirit/Online/NakamaSubsystem.h>
#include <Spirit/Character/Hero/HeroCharacter.h>
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
            //  UISubsystem->Display(this);
        }


        UNakamaSubsystem* Nakama = GameInstance->GetSubsystem<UNakamaSubsystem>();
        if (Nakama)
        {
            //  Nakama->AuthenticatePlayer();
        }
    }


    if (GetLocalPlayer())
    {
        EnhancedInputSubsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
        if (EnhancedInputSubsystem) {
            //  if (UIContext != nullptr) { SwitchInputContext(UIContext, 0); }
    
            AHeroCharacter* PlayerPawn = Cast<AHeroCharacter>(GetPawn());
            if (PlayerPawn)
            {
                //  UE_LOG(LogTemp, Warning, TEXT("Testing character?"))
                PlayerPawn->OnPawnPossessed.AddDynamic(this, &AHeroController::HandlePawnPossessed);
                PlayerPawn->OnPawnUnPossessed.AddDynamic(this, &AHeroController::HandlePawnUnPossessed);
            }
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







void AHeroController::HandlePawnPossessed()
{
    AHeroCharacter * PlayerPawn = Cast<AHeroCharacter>(GetPawn());
    if (PlayerPawn)
    {
        UInputMappingContext* PawnContext = PlayerPawn->GetInputContext();
        if (PawnContext)
        {
            SwitchInputContext(PawnContext, 0);
        }
    }
}

void AHeroController::HandlePawnUnPossessed()
{
    UE_LOG(LogTemp, Warning, TEXT("Unpossessed from controller???"))

    SwitchInputContext(UIContext, 0);
}