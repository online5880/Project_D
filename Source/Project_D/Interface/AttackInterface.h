#pragma once

#include "UObject/Interface.h"
#include "AttackInterface.generated.h"

UINTERFACE()
class UAttackInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECT_D_API IAttackInterface
{
	GENERATED_BODY()

public:
	virtual void Attack(){}
	virtual void Reload(){}
};
