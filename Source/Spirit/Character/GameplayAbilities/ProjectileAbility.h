// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "ProjectileAbility.generated.h"


class AProjectile;


UCLASS()
class SPIRIT_API UProjectileAbility : public UGameplayAbility
{
    GENERATED_BODY()

public:
    // Constructor
    UProjectileAbility();

    bool PerformLineTrace(FHitResult& OutHitResult);

    // Function to activate the ability
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_HandleResults(const FHitResult& HitResult);

protected:

    UPROPERTY(BlueprintReadWrite, Category = "Trace")
    float TraceDistance;

    // Projectile class to spawn
    UPROPERTY(EditDefaultsOnly, Category = "Projectile")
    TSubclassOf<AProjectile> ProjectileClass;

    // Spawn parameters for the projectile
    UPROPERTY(EditDefaultsOnly, Category = "Projectile")
    FVector LaunchVelocity;

    // Function to spawn the projectile
    void FireProjectile();



private:
    UFUNCTION(Server, Reliable, WithValidation)
    void Server_PerformTrace();
    void Server_PerformTrace_Implementation();
    bool Server_PerformTrace_Validate();

   
};