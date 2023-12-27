﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/Actor.h"
#include "Project_D/Interface/AttackInterface.h"
#include "BaseWeapon.generated.h"

class USphereComponent;

UCLASS()
class PROJECT_D_API ABaseWeapon : public AActor, public IAttackInterface
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

	// Overlap
	UFUNCTION()
	virtual void OnBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	virtual void OnEndOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	// Sphere Component
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category=  "Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> SphereComponent;

	// 무기 메쉬 - Static Mesh
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category=  "Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> WeaponStaticMeshComponent;

	// 무기 메쉬 - Skeletal Mesh
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category=  "Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> WeaponSkeletalMeshComponent;

	// Overlap 범위
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	float OverlapRadius = 30.f;
	
	// 무기 데미지
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category= "Weapon", meta = (AllowPrivateAccess = "true"))
	float Damage = 0.f;

public:
	FORCEINLINE float GetDamage() const {return Damage;}

	
};
