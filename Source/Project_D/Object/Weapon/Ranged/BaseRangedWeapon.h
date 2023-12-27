#pragma once

#include "Project_D/Object/Weapon/BaseWeapon.h"
#include "BaseRangedWeapon.generated.h"

class APDCharacter;

UCLASS()
class PROJECT_D_API ABaseRangedWeapon : public ABaseWeapon
{
	GENERATED_BODY()

public:

	ABaseRangedWeapon();

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
public:
	UPROPERTY()
	TObjectPtr<APDCharacter> OwnerCharacter;
};
