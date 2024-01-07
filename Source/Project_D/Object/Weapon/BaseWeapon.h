// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/Actor.h"
#include "Project_D/Interface/AttackInterface.h"
#include "Project_D/Interface/InteractInterface.h"
#include "BaseWeapon.generated.h"

class UMetaSoundSource;
class UAudioComponent;
class USphereComponent;

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	EWT_Rifle UMETA(DisplayName = "Rifle"),
	EWT_Pistol UMETA(DisplayName = "Pistol"),
	EWT_DefaultMAX UMETA(DisplayName = "MAX")
};


UCLASS()
class PROJECT_D_API ABaseWeapon : public AActor, public IAttackInterface, public IInteractInterface
{
	GENERATED_BODY()

public:

	ABaseWeapon();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// IAttackInterface
	virtual void Attack() override;
	virtual void Reload() override;

	// IInteractInterface
	virtual void Interact() override;

	// Overlap
	UFUNCTION()
	virtual void OnBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	virtual void OnEndOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/**
	 * member varialbes
	 */
	
	// Overlap 범위
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	float OverlapRadius = 30.f;
	
	// 무기 데미지
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category= "Weapon", meta = (AllowPrivateAccess = "true"))
	float Damage = 0.f;

	// 상호작용 가능한지
	bool bCanInteract;

	// Attach Socket Name
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category= "Weapon", meta = (AllowPrivateAccess = "true"))
	FName AttachSocketName = NAME_None;

#pragma region Sound
	// 오디오 컴포넌트
	UPROPERTY(EditDefaultsOnly, Category = "Component")
	TObjectPtr<UAudioComponent> AudioComponent;
	
	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<UMetaSoundSource> AttackSound;
private:
	
#pragma region Component
	// Sphere Component
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category=  "Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> SphereComponent;

	// 무기 메쉬 - Static Mesh
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category=  "Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> WeaponStaticMeshComponent;

	// 무기 메쉬 - Skeletal Mesh
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category=  "Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> WeaponSkeletalMeshComponent;

#pragma region ENUM
	// 무기 타입
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category=  "Weapon", meta = (AllowPrivateAccess = "true"))
	EWeaponType WeaponType;

public:
	FORCEINLINE UStaticMeshComponent*	GetWeaponStaticMesh() const {return WeaponStaticMeshComponent;}
	FORCEINLINE USkeletalMeshComponent* GetWeaponSkeletalMesh() const {return WeaponSkeletalMeshComponent;}
	FORCEINLINE float					GetDamage() const {return Damage;}
	FORCEINLINE EWeaponType				GetWeaponType() const {return WeaponType;}

	
};
