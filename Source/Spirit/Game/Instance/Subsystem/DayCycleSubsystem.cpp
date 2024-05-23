#include "DayCycleSubsystem.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Engine/Engine.h"
#include <Engine/DirectionalLight.h>
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include <Engine/SkyLight.h>

UDayCycleSubsystem::UDayCycleSubsystem()
    : CurrentTimeOfDay(0.0f), DayNightSpeed(1.0f), CurrentCycleState(EDayNightCycleState::None)
{
}



//  ----------------------------------------
//  TEST
//  ----------------------------------------
void UDayCycleSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    // Bind to the world initialization event
    FWorldDelegates::OnPostWorldInitialization.AddUObject(this, &UDayCycleSubsystem::HandlePostWorldInitialization);
}

void UDayCycleSubsystem::Deinitialize()
{
    Super::Deinitialize();

    // Clear the timer
    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().ClearTimer(TimerHandle);
        UE_LOG(LogTemp, Warning, TEXT("DayNightCycleSubsystem deinitialized and timer cleared."));
    }

    // Unbind from the world initialization event
    FWorldDelegates::OnPostWorldInitialization.RemoveAll(this);
}



//  ----------------------------------------
//  TEST
//  ----------------------------------------

void UDayCycleSubsystem::HandlePostWorldInitialization(UWorld* World, const UWorld::InitializationValues IVS)
{
    if (World == GetWorld())
    {
        // Find and assign the sunlight and moonlight actors based on their tags
        for (TActorIterator<ADirectionalLight> It(World); It; ++It)
        {
            ADirectionalLight* Light = *It;
            if (Light->ActorHasTag(TEXT("Sunlight")))
            {
                Sunlight = Light;
                UE_LOG(LogTemp, Warning, TEXT("Found Sunlight: %s"), *Light->GetName());
            }
        }
        for (TActorIterator<ASkyLight> It(World); It; ++It)
        {
            ASkyLight* Light = *It;
            if (Light->ActorHasTag(TEXT("Moonlight")))
            {
                Moonlight = Light;
                UE_LOG(LogTemp, Warning, TEXT("Found Moonlight: %s"), *Light->GetName());
            }
        }

        if (!Sunlight || !Moonlight)
        {
            UE_LOG(LogTemp, Warning, TEXT("Sunlight or Moonlight not found!"));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("DayNightCycleSubsystem initialized and timer set."));
        }

        InitializeKeySunPositions();

        // Set up the timer to call UpdateTimeOfDay at regular intervals
        World->GetTimerManager().SetTimer(TimerHandle, this, &UDayCycleSubsystem::UpdateTimeOfDay, 0.1f, true);

        // Broadcast the delegate
        OnDayNightCycleInitialized.Broadcast();
    }
}

void UDayCycleSubsystem::SetDayNightSpeed(float Speed)
{
    DayNightSpeed = Speed;
    UE_LOG(LogTemp, Warning, TEXT("DayNightSpeed set to: %f"), DayNightSpeed);
}



//  ----------------------------------------
//  TIME OF DAY
//  ----------------------------------------

void UDayCycleSubsystem::SetTimeOfDay(EDayNightCycleState NewTimeOfDay)
{
    CurrentCycleState = NewTimeOfDay;
    CurrentTimeOfDay = GetTimeOfDayFromState(NewTimeOfDay);

    // Ensure the lights are positioned correctly based on the new time of day
    float StateProgress = GetStateProgress(NewTimeOfDay);
    EDayNightCycleState NextState = GetNextCycleState(NewTimeOfDay);
    LerpLightRotations(StateProgress, NewTimeOfDay, NextState);
}


void UDayCycleSubsystem::UpdateTimeOfDay()
{
    if (UWorld* World = GetWorld())
    {
        float DeltaTime = 0.1f;
        CurrentTimeOfDay += DeltaTime * DayNightSpeed;

        if (CurrentTimeOfDay >= 24.0f)
        {
            CurrentTimeOfDay -= 24.0f;
            CurrentCycleState = EDayNightCycleState::None;
        }

        //  UE_LOG(LogTemp, Warning, TEXT("Current Time of Day: %f"), CurrentTimeOfDay);

        switch (CurrentCycleState)
        {
        case EDayNightCycleState::None:
            if (CurrentTimeOfDay >= 0.0f)
            {
                OnTimeMidnight.Broadcast();
                CurrentCycleState = EDayNightCycleState::Midnight;
            }
            break;
        case EDayNightCycleState::Midnight:
            if (CurrentTimeOfDay >= 6.0f)
            {
                OnTimeDawn.Broadcast();
                CurrentCycleState = EDayNightCycleState::Dawn;
            }
            break;
        case EDayNightCycleState::Dawn:
            if (CurrentTimeOfDay >= 12.0f)
            {
                OnTimeNoon.Broadcast();
                CurrentCycleState = EDayNightCycleState::Noon;
            }
            break;
        case EDayNightCycleState::Noon:
            if (CurrentTimeOfDay >= 18.0f)
            {
                OnTimeDusk.Broadcast();
                CurrentCycleState = EDayNightCycleState::Dusk;
            }
            break;
        case EDayNightCycleState::Dusk:
            break;
        }

        float StateProgress = GetStateProgress(CurrentCycleState);
        EDayNightCycleState NextState = GetNextCycleState(CurrentCycleState);

        LerpLightRotations(StateProgress, CurrentCycleState, NextState);

        // Adjust moonlight intensity based on time of day
        if (CurrentTimeOfDay >= SunsetStartTime && CurrentTimeOfDay <= SunsetEndTime)
        {
            //  RampUpMoonLight(DeltaTime);
        }
        else if (CurrentTimeOfDay >= SunriseStartTime && CurrentTimeOfDay <= SunriseEndTime)
        {
            //  RampDownMoonLight(DeltaTime);
        }
    }
}




/*
void UDayCycleSubsystem::RampUpMoonLight(float DeltaTime)
{
    if (Moonlight)
    {
        float CurrentIntensity = Moonlight->GetLightComponent()->Intensity;
        float TargetIntensity = 4.0f;
        float RampUpSpeed = TargetIntensity / (SunsetEndTime - SunsetStartTime);
        float NewIntensity = FMath::Clamp(CurrentIntensity + RampUpSpeed * DeltaTime, 0.0f, TargetIntensity);
        Moonlight->GetLightComponent()->SetIntensity(NewIntensity);
    }
}

void UDayCycleSubsystem::RampDownMoonLight(float DeltaTime)
{
    if (Moonlight)
    {
        float CurrentIntensity = Moonlight->GetLightComponent()->Intensity;
        float TargetIntensity = 0.0f;
        float RampDownSpeed = 4.0f / (SunriseEndTime - SunriseStartTime);
        float NewIntensity = FMath::Clamp(CurrentIntensity - RampDownSpeed * DeltaTime, 0.0f, 4.0f);
        Moonlight->GetLightComponent()->SetIntensity(NewIntensity);
    }
}

*/


void UDayCycleSubsystem::LerpLightRotations(float Progress, EDayNightCycleState FromState, EDayNightCycleState ToState)
{
    if (Sunlight)
    {
        FRotator SunStart = SunPositions.FindRef(FromState);
        FRotator SunEnd = SunPositions.FindRef(ToState);
        FRotator SunRotation = FMath::Lerp(SunStart, SunEnd, Progress);
        Sunlight->SetActorRotation(SunRotation);
    }
    if (Moonlight)
    {
        FRotator MoonStart = MoonPositions.FindRef(FromState);
        FRotator MoonEnd = MoonPositions.FindRef(ToState);
        FRotator MoonRotation = FMath::Lerp(MoonStart, MoonEnd, Progress);
        Moonlight->SetActorRotation(MoonRotation);
    }
}

void UDayCycleSubsystem::InitializeKeySunPositions()
{
    if (Sunlight)
    {
        SunPositions.Add(EDayNightCycleState::Midnight, FRotator(-90.0f, 0.0f, 0.0f)); // Midnight (below horizon)
        SunPositions.Add(EDayNightCycleState::Dawn, FRotator(0.0f, 0.0f, 0.0f)); // Dawn (east)
        SunPositions.Add(EDayNightCycleState::Noon, FRotator(90.0f, 0.0f, 0.0f)); // Noon (highest point)
        SunPositions.Add(EDayNightCycleState::Dusk, FRotator(0.0f, 180.0f, 0.0f)); // Dusk (west)
    }

    if (Moonlight)
    {
        MoonPositions.Add(EDayNightCycleState::Midnight, FRotator(90.0f, 0.0f, 0.0f)); // Midnight (highest point)
        MoonPositions.Add(EDayNightCycleState::Dawn, FRotator(180.f, 0.0f, 0.0f)); // Dawn (setting in the west)
        MoonPositions.Add(EDayNightCycleState::Noon, FRotator(-180.0f, 0.0f, 0.0f)); // Noon (below horizon)
        MoonPositions.Add(EDayNightCycleState::Dusk, FRotator(0.0f, 0.0f, 0.0f)); // Dusk (rising in the east)
    }
}

float UDayCycleSubsystem::GetTimeOfDayFromState(EDayNightCycleState State)
{
    switch (State)
    {
    case EDayNightCycleState::Midnight:
        return 0.0f;
    case EDayNightCycleState::Dawn:
        return 6.0f;
    case EDayNightCycleState::Noon:
        return 12.0f;
    case EDayNightCycleState::Dusk:
        return 18.0f;
    default:
        return 0.0f;
    }
}

float UDayCycleSubsystem::GetStateProgress(EDayNightCycleState CurrentState)
{
    float StateStartTime = GetTimeOfDayFromState(CurrentState);
    float NextStateTime = GetTimeOfDayFromState(GetNextCycleState(CurrentState));
    return (CurrentTimeOfDay - StateStartTime) / (NextStateTime - StateStartTime);
}

EDayNightCycleState UDayCycleSubsystem::GetNextCycleState(EDayNightCycleState CurrentState)
{
    switch (CurrentState)
    {
    case EDayNightCycleState::Midnight:
        return EDayNightCycleState::Dawn;
    case EDayNightCycleState::Dawn:
        return EDayNightCycleState::Noon;
    case EDayNightCycleState::Noon:
        return EDayNightCycleState::Dusk;
    case EDayNightCycleState::Dusk:
        return EDayNightCycleState::Midnight;
    default:
        return EDayNightCycleState::None;
    }
}