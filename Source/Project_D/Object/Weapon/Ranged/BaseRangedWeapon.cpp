#include "BaseRangedWeapon.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Project_D/Character/PDCharacter.h"

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

void ABaseRangedWeapon::Interact()
{
	Super::Interact();

	// 상호작용 로직 구현
	if(bCanInteract && OwnerCharacter)
	{
		if(IInteractInterface* Interact = Cast<IInteractInterface>(OwnerCharacter))
		{
			Interact->PickupWeapon(this,AttachSocketName);
		}
	}
}

void ABaseRangedWeapon::OnBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBeginOverlapEvent(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	// Overlap 시작 시 처리
	OwnerCharacter = Cast<APDCharacter>(OtherActor);
	if(OwnerCharacter)
	{
		OwnerCharacter->SetOverlappedActor(this);
	}
	bCanInteract = true;
}

void ABaseRangedWeapon::OnEndOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnEndOverlapEvent(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	// Overlap 종료 시 처리
	if(OwnerCharacter)
	{
		OwnerCharacter->SetOverlappedActor(nullptr);
		OwnerCharacter = nullptr;
	}
	bCanInteract = false;
}

