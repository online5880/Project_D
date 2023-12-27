#pragma once

#include "Project_D/Object/Weapon/BaseWeapon.h"
#include "BaseRifle.generated.h"

UCLASS()
class PROJECT_D_API ABaseRifle : public ABaseWeapon
{
	GENERATED_BODY()

public:

	ABaseRifle();

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// IAttackComponent
	virtual void Attack() override;
	virtual void Reload() override;

	// Overlap
	virtual void OnBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnEndOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
public:

	
};
