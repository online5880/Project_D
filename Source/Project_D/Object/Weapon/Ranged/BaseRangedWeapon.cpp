#include "BaseRangedWeapon.h"

#include "MetasoundSource.h"
#include "NiagaraFunctionLibrary.h"
#include "Ammo/BaseRangedAmmo.h"
#include "Animation/AnimInstance.h"
#include "Components/AudioComponent.h"
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

	if(OwnerCharacter && OwnerCharacter->GetIsAiming() && FireMontage)
	{
		OwnerCharacter->GetMesh()->GetAnimInstance()->Montage_Play(FireMontage);
	}
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
			//this->SetActorEnableCollision(false);
		}
	}
}

void ABaseRangedWeapon::OnBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBeginOverlapEvent(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	// Overlap 시작 시 처리
	if(OtherActor == UGameplayStatics::GetPlayerCharacter(GetWorld(),0))
	{
		OwnerCharacter = Cast<APDCharacter>(OtherActor);
		if(OwnerCharacter)
		{
			OwnerCharacter->SetOverlappedActor(this);
		}
		bCanInteract = true;
	}
}

void ABaseRangedWeapon::OnEndOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnEndOverlapEvent(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	// Overlap 종료 시 처리
	if(OtherActor == UGameplayStatics::GetPlayerCharacter(GetWorld(),0))
	{
		if(OwnerCharacter)
		{
			OwnerCharacter->SetOverlappedActor(nullptr);
			OwnerCharacter = nullptr;
		}
		bCanInteract = false;
	}
}

void ABaseRangedWeapon::PlayAttackSound()
{
	AudioComponent->Stop();
	AudioComponent->SetSound(AttackSound);
	AudioComponent->Play();
}

void ABaseRangedWeapon::SpawnFireEffect()
{
	const FTransform SocketTransform = GetWeaponSkeletalMesh()->GetSocketTransform(MuzzleSocketName);
	const UWorld* World = GetWorld();
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(World,FireEffect,SocketTransform.GetLocation(),SocketTransform.Rotator()+FRotator(-90.f,0.f,0.f));
}

void ABaseRangedWeapon::SpawnProjectile()
{
	const FTransform SocketTransform = GetWeaponSkeletalMesh()->GetSocketTransform(MuzzleSocketName);
	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.Instigator = GetInstigator();
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			
	CurrentRangedAmmo = GetWorld()->SpawnActor<ABaseRangedAmmo>(DefaultRangedAmmo,SocketTransform.GetLocation(),SocketTransform.Rotator());
}

void ABaseRangedWeapon::Fire()
{
	if(OwnerCharacter && AttackSound && FireEffect && DefaultRangedAmmo)
	{
		PlayAttackSound();
		SpawnFireEffect();
		SpawnProjectile();
	}
}

