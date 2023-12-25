#include "FootStepComponent.h"
#include UE_INLINE_GENERATED_CPP_BY_NAME(FootStepComponent)

UFootStepComponent::UFootStepComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

}


void UFootStepComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UFootStepComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UFootStepComponent::FootStep()
{
}

void UFootStepComponent::FootStepSphereTrace()
{
}

