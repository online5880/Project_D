#pragma once

#include "Components/ActorComponent.h"
#include "FootStepComponent.generated.h"


/**
 * Foot Step Component
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_D_API UFootStepComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFootStepComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

	// Foot Step(Sound, Effect...)
	void FootStep();
protected:

	// Sphere Trace
	void FootStepSphereTrace();
private:
	UPROPERTY()
	TObjectPtr<ACharacter> Character;
	
};
