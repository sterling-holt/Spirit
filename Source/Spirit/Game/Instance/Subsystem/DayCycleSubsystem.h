#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Engine/DirectionalLight.h"
#include "DayCycleSubsystem.generated.h"

UENUM(BlueprintType)
enum class EDayNightCycleState : uint8
{
    Midnight UMETA(DisplayName = "Midnight"),
    Dawn UMETA(DisplayName = "Dawn"),
    Noon UMETA(DisplayName = "Noon"),
    Dusk UMETA(DisplayName = "Dusk"),
    None UMETA(DisplayName = "None")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimeDawn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimeNoon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimeDusk);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimeMidnight);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDayNightCycleInitialized);

UCLASS()
class SPIRIT_API UDayCycleSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    UDayCycleSubsystem();

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    UFUNCTION(BlueprintCallable, Category = "DayNightCycle")
    void SetDayNightSpeed(float Speed);

    UFUNCTION(BlueprintCallable, Category = "DayNightCycle")
    void SetTimeOfDay(EDayNightCycleState NewTimeOfDay);

    UPROPERTY(BlueprintAssignable, Category = "DayNightCycle")
    FOnTimeDawn OnTimeDawn;

    UPROPERTY(BlueprintAssignable, Category = "DayNightCycle")
    FOnTimeNoon OnTimeNoon;

    UPROPERTY(BlueprintAssignable, Category = "DayNightCycle")
    FOnTimeDusk OnTimeDusk;

    UPROPERTY(BlueprintAssignable, Category = "DayNightCycle")
    FOnTimeMidnight OnTimeMidnight;

    UPROPERTY(BlueprintAssignable, Category = "DayNightCycle")
    FOnDayNightCycleInitialized OnDayNightCycleInitialized;




        void UpdateDayCycle(float DeltaTime);

protected:
    void HandlePostWorldInitialization(UWorld* World, const UWorld::InitializationValues IVS);
    void UpdateTimeOfDay();
    void LerpLightRotations(float Progress, EDayNightCycleState FromState, EDayNightCycleState ToState);
    void InitializeKeySunPositions();
    float GetTimeOfDayFromState(EDayNightCycleState State);
    float GetStateProgress(EDayNightCycleState CurrentState);
    EDayNightCycleState GetNextCycleState(EDayNightCycleState CurrentState);




    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DayCycle")
    float SunsetStartTime; // Time of day when sunset starts

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DayCycle")
    float SunsetEndTime; // Time of day when sunset ends

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DayCycle")
    float SunriseStartTime; // Time of day when sunrise starts

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DayCycle")
    float SunriseEndTime; // Time of day when sunrise ends

    void RampUpMoonLight(float DeltaTime);
    void RampDownMoonLight(float DeltaTime);






private:
    UPROPERTY(EditAnywhere, Category = "DayNightCycle")
    AActor* Sunlight;

    UPROPERTY(EditAnywhere, Category = "DayNightCycle")
    AActor* Moonlight;

    FTimerHandle TimerHandle;

    UPROPERTY(BlueprintReadWrite, Category = "DayNightCycle", meta = (AllowPrivateAccess = "true"))
    float CurrentTimeOfDay;

    UPROPERTY(EditAnywhere, Category = "DayNightCycle")
    float DayNightSpeed;

    EDayNightCycleState CurrentCycleState;

    TMap<EDayNightCycleState, FRotator> SunPositions;
    TMap<EDayNightCycleState, FRotator> MoonPositions;
};