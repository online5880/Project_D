#include "BaseRifle.h"
#include UE_INLINE_GENERATED_CPP_BY_NAME(BaseRifle)

ABaseRifle::ABaseRifle()
{

	PrimaryActorTick.bCanEverTick = true;
}

void ABaseRifle::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseRifle::Attack()
{
	Super::Attack();
}

void ABaseRifle::Reload()
{
	Super::Reload();
}

void ABaseRifle::OnBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBeginOverlapEvent(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void ABaseRifle::OnEndOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnEndOverlapEvent(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

