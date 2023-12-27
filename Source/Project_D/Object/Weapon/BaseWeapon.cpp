// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(BaseWeapon)

ABaseWeapon::ABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SphereComponent->SetSphereRadius(OverlapRadius);
	SetRootComponent(SphereComponent);

	WeaponStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	WeaponStaticMeshComponent->SetupAttachment(GetRootComponent());

	WeaponSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	WeaponSkeletalMeshComponent->SetupAttachment(GetRootComponent());
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&ThisClass::OnBeginOverlapEvent);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this,&ThisClass::OnEndOverlapEvent);
}

void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseWeapon::Attack()
{
	IAttackInterface::Attack();
}

void ABaseWeapon::Reload()
{
	IAttackInterface::Reload();
}

void ABaseWeapon::Interact()
{
}

void ABaseWeapon::OnBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ABaseWeapon::OnEndOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

