#pragma once

#include "GameFramework/Actor.h"
#include "BaseRangedAmmo.generated.h"

class UMaterialInterface;
class UNiagaraSystem;
class UCapsuleComponent;
class UProjectileMovementComponent;
class UStaticMeshComponent;

UCLASS()
class PROJECT_D_API ABaseRangedAmmo : public AActor
{
	GENERATED_BODY()

public:

	ABaseRangedAmmo();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Overlap
	UFUNCTION()
	virtual void OnBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnEndOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// Projectile
	UFUNCTION()
	virtual void OnProjectileStop(const FHitResult& ImpactResult);
	UFUNCTION()
	virtual void OnProjectileBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity);
	

	// 총알 메쉬
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,  Category = "Ammo")
	TObjectPtr<UStaticMeshComponent> AmmoMesh;

	// 총알 콜리전
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,  Category = "Ammo")
	TObjectPtr<UCapsuleComponent> AmmoCollision;

	// Projectile Movement Component
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,  Category = "Ammo")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

private:
	// 총알 속도
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Ammo", meta = (AllowPrivateAccess = "true"))
	float BulletSpeed;

	// 총알 데미지
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Ammo", meta = (AllowPrivateAccess = "true"))
	float BulletDamage;

	// 총알 범위(유효 사거리, 범위를 넘어가면 사라짐)
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Ammo", meta = (AllowPrivateAccess = "true"))
	float BulletRange;

	// 총알 맞았을 때 이펙트
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Effect", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UNiagaraSystem> HitEffect;

	// 총알 맞았을 때 데칼
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Effect", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMaterialInterface> HitDecal;

	// 데칼 사이즈
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Effect", meta = (AllowPrivateAccess = "true"))
	FVector DecalSize = FVector(4.f,8.f,8.f);
	
};
