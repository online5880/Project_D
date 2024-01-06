#pragma once

#include "Project_D/Object/Weapon/BaseWeapon.h"
#include "BaseRangedWeapon.generated.h"

class UNiagaraSystem;
class UAnimMontage;
class APDCharacter;

UCLASS()
class PROJECT_D_API ABaseRangedWeapon : public ABaseWeapon
{
	GENERATED_BODY()

public:

	ABaseRangedWeapon();

	// 발사
	void Fire();
protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// IAttackComponent
	virtual void Attack() override;
	virtual void Reload() override;

	// IInteractInterface
	virtual void Interact() override;

	// Overlap
	virtual void OnBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnEndOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	// member method
	
	UPROPERTY()
	TObjectPtr<APDCharacter> OwnerCharacter;

	// 총 발사 이펙트(나이아가라)
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Effect", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UNiagaraSystem> FireEffect;

	// 발사 소켓 이름
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Effect", meta = (AllowPrivateAccess = "true"))
	FName MuzzleSocketName;
private:
	// 발사 몽타주
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Montage", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> FireMontage;

	// 장전 몽타주
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Montage", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> ReloadMontage;
};
