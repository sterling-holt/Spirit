#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Particles/ParticleSystem.h"
#include "FireBlastAbility.generated.h"

UCLASS()
class SPIRIT_API UFireBlastAbility : public UGameplayAbility
{
    GENERATED_BODY()

public:
    UFireBlastAbility();

    // Particle System for the fire blast effect
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
    UParticleSystem* FireBlastEffect;

    // Ability activation logic
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
