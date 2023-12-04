#include "PDAnimInstance.h"
#include "AnimGraphRuntime/Public/KismetAnimationLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Project_D/Character/PDCharacter.h"

UPDAnimInstance::UPDAnimInstance()
{
}

void UPDAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (Character == nullptr)
	{
		Character = Cast<APDCharacter>(GetOwningActor());
		if (Character)
		{
			MovementComponent = Cast<UCharacterMovementComponent>(Character->GetMovementComponent());
		}
	}
}

void UPDAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Character && MovementComponent)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(MovementComponent->Velocity);
		Direction = UKismetMathLibrary::NormalizeAxis(UKismetAnimationLibrary::CalculateDirection(MovementComponent->Velocity, Character->GetActorRotation()));
		ShouldMove = MovementComponent->GetCurrentAcceleration().IsNearlyZero() && GroundSpeed > 3.f ? true : false;
		IsFalling = MovementComponent->IsFalling();
	}
}
