#include "BaseRangedAmmo.h"

#include "NiagaraFunctionLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

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
	AmmoCollision->OnComponentHit.AddDynamic(this,&ThisClass::OnHit);

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

void ABaseRangedAmmo::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//DrawDebugSphere(GetWorld(),Hit.ImpactPoint,2.5f,8,FColor::Orange,false,3.f,0,1.f);
	if(HitEffect && HitDecal)
	{
		if(const UWorld* World = GetWorld())
		{
			const FVector HitLocation(Hit.ImpactPoint);
			const FRotator HitRotation(Hit.ImpactNormal.ToOrientationRotator());
			
			// Decal
			UGameplayStatics::SpawnDecalAtLocation(World,HitDecal,DecalSize,HitLocation,HitRotation,1.f);

			// Effect
			const FRotator EffectRotation(HitRotation+FRotator(-90.f,0.f,0.f));
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(World,HitEffect,HitLocation,EffectRotation);

			Destroy();
		}
	}
}


void ABaseRangedAmmo::OnProjectileStop(const FHitResult& ImpactResult)
{
	
}

void ABaseRangedAmmo::OnProjectileBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity)
{
	
}
