#include "Projectile.h"

AProjectile::AProjectile()
{
    // Create the projectile movement component and initialize values
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->UpdatedComponent = RootComponent;
    ProjectileMovement->InitialSpeed = 3000.f;
    ProjectileMovement->MaxSpeed = 3000.f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce = true;

    // Set this actor to call Tick() every frame. You can disable this if not needed.
    PrimaryActorTick.bCanEverTick = true;
}

void AProjectile::BeginPlay()
{
    Super::BeginPlay();
}

void AProjectile::LaunchProjectile(FVector LaunchVelocity)
{
    ProjectileMovement->Velocity = LaunchVelocity;
}
