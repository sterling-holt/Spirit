#include "ProjectileAbility.h"
#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include <Spirit/Character/SpiritCharacter.h>

UProjectileAbility::UProjectileAbility()
{
    //  Set the ability to be non-passive and instanced per actor
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
    //  
    //  // Set default value for the FireBlastEffect (ensure this path is correct for your project)
    //  static ConstructorHelpers::FObjectFinder<UParticleSystem> FireBlastEffectAsset(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));
    //  if (FireBlastEffectAsset.Succeeded())
    //  {
    //      FireBlastEffect = FireBlastEffectAsset.Object;
    //  }

    TraceDistance = 10000.f;
    UE_LOG(LogTemp, Warning, TEXT("Projectile Ability initalized"))
}

void UProjectileAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    if (GetOwningActorFromActorInfo()->GetLocalRole() == ROLE_Authority)
    {
        Server_PerformTrace();

        FHitResult HitResult;
        if (PerformLineTrace(HitResult))
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Fire Blast Activated!"));
        }
    }
    EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}


bool UProjectileAbility::PerformLineTrace(FHitResult& OutHitResult)
{
    APlayerController* PC = Cast<APlayerController>(GetOwningActorFromActorInfo()->GetInstigatorController());
    if (!PC || !GetOwningActorFromActorInfo())
    {
        return false;
    }

    FVector StartLocation;
    FRotator ViewpointRotation;
    PC->GetPlayerViewPoint(StartLocation, ViewpointRotation); // Get the camera location and rotation

    FVector FirstTraceEnd = StartLocation + (ViewpointRotation.Vector() * TraceDistance); // Determine the endpoint of the first trace

    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(GetOwningActorFromActorInfo());
    QueryParams.bTraceComplex = true;
    QueryParams.bReturnPhysicalMaterial = false;

    FHitResult FirstTraceHitResult;
    bool bFirstHit = GetWorld()->LineTraceSingleByChannel(
        FirstTraceHitResult,
        StartLocation,
        FirstTraceEnd,
        ECC_GameTraceChannel1,  // Adjust this as necessary for your game
        QueryParams
    );

    FCollisionShape CollShape = FCollisionShape::MakeSphere(10.0f);
    bool bHit = GetWorld()->SweepSingleByChannel(
        FirstTraceHitResult,
        StartLocation,
        FirstTraceEnd,
        FQuat::Identity,
        ECC_GameTraceChannel1,
        CollShape,
        QueryParams
    );


    //  Determine the start point for the second trace
    //  FVector SecondTraceStart = GetOwningActorFromActorInfo()->GetActorLocation() + FVector(0, 0, GetCapsuleComponentHalfHeight()); // Adjust vertical offset based on the character's capsule component

    FVector SecondTraceStart = GetOwningActorFromActorInfo()->GetActorLocation();
    UCapsuleComponent* CapsuleComp = Cast<UCapsuleComponent>(GetOwningActorFromActorInfo()->FindComponentByClass<UCapsuleComponent>());
    if (CapsuleComp)
    {
        SecondTraceStart.Z += CapsuleComp->GetScaledCapsuleHalfHeight();  // Adjust for capsule's half-height
    }

    // Determine the end point for the second trace
    FVector SecondTraceEnd = bFirstHit ? FirstTraceHitResult.ImpactPoint : FirstTraceEnd;

    bool bSecondHit = GetWorld()->LineTraceSingleByChannel(
        OutHitResult,
        SecondTraceStart,
        SecondTraceEnd,
        ECC_GameTraceChannel1,
        QueryParams
    );

    // Optionally draw the line for debugging
#if WITH_EDITOR
    DrawDebugLine(GetWorld(), SecondTraceStart, SecondTraceEnd, bSecondHit ? FColor::Green : FColor::Red, false, 5.f, 0, 1.f);
#endif

    return bSecondHit;
}
/*
*/





void UProjectileAbility::Server_PerformTrace_Implementation()
{
    UE_LOG(LogTemp, Warning, TEXT("Performing Trace?"))
    ACharacter* CharacterOwner = Cast<ASpiritCharacter>(GetOwningActorFromActorInfo());
    if (!CharacterOwner)
    {
        return;
    }

    FVector StartLocation = CharacterOwner->GetActorLocation();
    FVector ForwardDirection = CharacterOwner->GetActorForwardVector();
    FVector EndLocation = StartLocation + (ForwardDirection * 1000.0f);  // Adjust trace distance as needed

    FHitResult HitResult;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(CharacterOwner);
    QueryParams.bTraceComplex = true;

    if (GetWorld()->LineTraceSingleByChannel(
        HitResult,
        StartLocation,
        EndLocation,
        ECC_Visibility,  // Adjust collision channel as necessary
        QueryParams))
    {
        //  Multicast_HandleResults(HitResult);
    }
}

bool UProjectileAbility::Server_PerformTrace_Validate()
{
    return true;  // Add validation logic if necessary
}

void UProjectileAbility::Multicast_HandleResults_Implementation(const FHitResult& HitResult)
{
    //  Handle hit result, e.g., applying effects, damage, etc.
    //  Debug visualization
    //  if (GetWorld()->GetNetMode() != NM_Client)
    //  {
    //      DrawDebugLine(GetWorld(), HitResult.TraceStart, HitResult.TraceEnd, FColor::Red, false, 5.0f);
    //  }

#if UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT
    if (GetWorld())
    {
        // Draw the debug line
        DrawDebugLine(
            GetWorld(),
            HitResult.TraceStart,
            HitResult.TraceEnd,
            FColor::Red,    // Line color
            false,          // Persistent lines
            5.0f,           // Lifetime of line in seconds
            0,              // Depth priority
            5.0f            // Line thickness
        );
    }
#endif
}
/*
*/