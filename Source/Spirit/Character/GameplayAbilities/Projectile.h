
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class SPIRIT_API AProjectile : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AProjectile();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Projectile movement component
    UPROPERTY(VisibleAnywhere, Category = "Movement")
    UProjectileMovementComponent* ProjectileMovement;

    // Function to initialize the projectile's velocity in the shoot direction
    void LaunchProjectile(FVector LaunchVelocity);
};