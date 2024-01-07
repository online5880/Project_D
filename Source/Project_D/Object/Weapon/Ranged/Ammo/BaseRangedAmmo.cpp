#include "BaseRangedAmmo.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(BaseRangedAmmo)

ABaseRangedAmmo::ABaseRangedAmmo()
{
	PrimaryActorTick.bCanEverTick = true;

	AmmoCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Ammo Collision"));
	AmmoCollision->SetRelativeRotation(FRotator(0,-90.f,90.f));
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
}

void ABaseRangedAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseRangedAmmo::OnBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(1,3.f,FColor::Orange,__FUNCTION__);
}

void ABaseRangedAmmo::OnEndOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

