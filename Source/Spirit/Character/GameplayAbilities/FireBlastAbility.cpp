#include "FireBlastAbility.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"

UFireBlastAbility::UFireBlastAbility()
{
    //  InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
    //  
    //  // Set default value for the FireBlastEffect (ensure this path is correct for your project)
    //  static ConstructorHelpers::FObjectFinder<UParticleSystem> FireBlastEffectAsset(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));
    //  if (FireBlastEffectAsset.Succeeded())
    //  {
    //      FireBlastEffect = FireBlastEffectAsset.Object;
    //  }
}

void UFireBlastAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    //  if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
    //  {
    //      if (FireBlastEffect)
    //      {
    //          // Spawn the fire blast particle effect
    //          FVector Location = ActorInfo->AvatarActor->GetActorLocation() + ActorInfo->AvatarActor->GetActorForwardVector() * 100.0f; // Adjust the location as needed
    //          UGameplayStatics::SpawnEmitterAtLocation(this, FireBlastEffect, Location);
    //  
    //          // Log a message for demonstration purposes
    //          if (GEngine)
    //          {
    //              GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Fire Blast Activated!"));
    //          }
    //      }
    //  
    //      // End the ability
    //      EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
    //  }
}
