// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UInteractInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECT_D_API IInteractInterface
{
	GENERATED_BODY()

public:
	// 상호작용
	virtual void Interact() = 0;

	// 무기 줍기
	virtual void PickupWeapon(class ABaseWeapon* NewWeapon,const FName& SocketName){}
};
