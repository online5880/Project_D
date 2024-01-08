#include "BaseRangedAmmo.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(BaseRangedAmmo)

ABaseRangedAmmo::ABaseRangedAmmo()
{
	PrimaryActorTick.bCanEverTick = true;

	AmmoCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Ammo Collision"));
	AmmoCollision->SetRelativeRotation(FRotator(-90.f,0.f,0.f));
	SetRootComponent(AmmoCollision);
	
	AmmoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ammo Mesh"));
	AmmoMesh->SetupAttachment(GetRootComponent());
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
}

void ABaseRangedAmmo::BeginPlay()
{
	Super::BeginPlay();
	
	AmmoCollision->OnComponentBeginOverlap.AddDynamic(this,&ThisClass::OnBeginOverlapEvent);
	AmmoCollision->OnComponentEndOverlap.AddDynamic(this,&ThisClass::OnEndOverlapEvent);

	ProjectileMovementComponent->OnProjectileStop.AddDynamic(this,&ThisClass::OnProjectileStop);
	ProjectileMovementComponent->OnProjectileBounce.AddDynamic(this,&ThisClass::OnProjectileBounce);
}

void ABaseRangedAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseRangedAmmo::OnBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void ABaseRangedAmmo::OnEndOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

void ABaseRangedAmmo::OnProjectileStop(const FHitResult& ImpactResult)
{
	DrawDebugSphere(GetWorld(),ImpactResult.ImpactPoint,10.f,8,FColor::Orange,false,3.f,0,1.f);
}

void ABaseRangedAmmo::OnProjectileBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity)
{
	
}

