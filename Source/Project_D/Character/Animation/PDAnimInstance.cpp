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
		GroundSpeed = UKismetMathLibrary::VSizeXY(Character->GetVelocity());
		Direction = UKismetMathLibrary::NormalizeAxis(UKismetAnimationLibrary::CalculateDirection(MovementComponent->Velocity, Character->GetActorRotation()));
		bShouldMove = MovementComponent->GetCurrentAcceleration().IsNearlyZero() && GroundSpeed > 3.f ? true : false;
		bIsFalling = MovementComponent->IsFalling();
		bIsCrouching = Character->GetIsCrouching();
		ForwardInputValue = Character->GetForwardInputValue();
		RightInputValue = Character->GetRightInputValue();

		const FRotator AimRotation = Character->GetBaseAimRotation();
		const FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(Character->GetVelocity());
		MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation,AimRotation).Yaw;

		if(GroundSpeed > 0.f)
		{
			LastMovementOffsetYaw = MovementOffsetYaw;
		}
		
		TurnInPlace();
	}
}

void UPDAnimInstance::TurnInPlace()
{
	if (Character == nullptr) return;
	if(GroundSpeed > 0.f)
	{
		RootYawOffset = 0.f;
		CharacterYaw = Character->GetActorRotation().Yaw;
		CharacterYawLastFrame = CharacterYaw;
		RotationCurveLastFrame = 0.f;
		RotationCurve = 0.f;
	}
	else
	{
		CharacterYawLastFrame = CharacterYaw;
		CharacterYaw = Character->GetActorRotation().Yaw;
		const float YawDelta{ CharacterYaw - CharacterYawLastFrame };
		
		RootYawOffset = UKismetMathLibrary::NormalizeAxis(RootYawOffset-YawDelta);
		
		const float Turning{GetCurveValue(TEXT("Turning"))};
		if(Turning > 0)
		{
			RotationCurveLastFrame = RotationCurve;
			RotationCurve = GetCurveValue(TEXT("Rotation"));
			const float DeltaRotation{RotationCurve - RotationCurveLastFrame};

			// RootYawOffset > 0 -> 왼쪽으로 회전, RootYawOffset < 0 -> 오른쪽으로 회전
			RootYawOffset > 0 ? RootYawOffset -= DeltaRotation : RootYawOffset += DeltaRotation;

			const float ABSRootYawOffset{FMath::Abs(RootYawOffset)};
			if(ABSRootYawOffset > 90.f)
			{
				const float YawExcess{ABSRootYawOffset-90.f};
				RootYawOffset > 0 ? RootYawOffset -= YawExcess : RootYawOffset += YawExcess;
			}
		}
	}
}
