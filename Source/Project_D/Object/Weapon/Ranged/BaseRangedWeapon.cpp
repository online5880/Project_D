#include "BaseRangedWeapon.h"

#include "Engine/Engine.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(BaseRangedWeapon)

ABaseRangedWeapon::ABaseRangedWeapon()
{

	PrimaryActorTick.bCanEverTick = true;
}

void ABaseRangedWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseRangedWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseRangedWeapon::Attack()
{
	Super::Attack();
}

void ABaseRangedWeapon::Reload()
{
	Super::Reload();
}

void ABaseRangedWeapon::OnBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBeginOverlapEvent(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Orange,__FUNCTION__);
}

void ABaseRangedWeapon::OnEndOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnEndOverlapEvent(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Orange,__FUNCTION__);
}

