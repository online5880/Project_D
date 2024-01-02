#include "PDAnimInstance.h"
#include "AnimGraphRuntime/Public/KismetAnimationLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Project_D/Character/PDCharacter.h"
#include "Project_D/Character/Component/FootStepComponent.h"

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
		CombatState = Character->GetCharacterCombatState();
		
		/*const FRotator AimRotation = Character->GetBaseAimRotation();
		const FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(Character->GetVelocity());
		MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation,AimRotation).Yaw;
		*/
		
		CalcHeadRotation(80.f,50.f,5.f,DeltaSeconds);
		CalcAimOffset(5.f,DeltaSeconds);
	}
}

void UPDAnimInstance::CalcHeadRotation(const float MaxLeftRight, const float MaxUpDown, const float Speed, const float Delta)
{
	// 캐릭터가 없으면 함수를 종료합니다.
	if (!Character)
		return;

	// 컨트롤러와 액터의 회전값을 가져옵니다.
	const FRotator ControlRotation = Character->GetControlRotation();
	const FRotator ActorRotation = Character->GetActorRotation();

	// 머리 회전을 위한 새로운 회전값을 계산합니다.
	const float YawDifference = ControlRotation.Yaw - ActorRotation.Yaw;
	const float InvertedRoll = ControlRotation.Pitch * -1.0f;
	const FRotator NewRotation(0.0f, YawDifference, InvertedRoll);

	// 최대 회전 범위 내에서 머리 회전을 제한합니다.
	const float ClampedYaw = FMath::ClampAngle(NewRotation.Yaw, -MaxLeftRight, MaxLeftRight);
	const float ClampedRoll = FMath::ClampAngle(NewRotation.Roll, -MaxUpDown, MaxUpDown);
	const FRotator ClampedRotation(0.0f, ClampedYaw, ClampedRoll);

	// 머리 회전이 최대 각도를 넘는지 확인하고, 필요에 따라 보간합니다.
	const float YawAbs = FMath::Abs(YawDifference);
	const bool bIsYawOutOfRange = YawAbs > MaxLeftRight + 360.0f || (YawAbs > MaxLeftRight && YawDifference < 360.0f - MaxLeftRight);
	if (bIsYawOutOfRange)
	{
		HeadRotation = UKismetMathLibrary::RInterpTo(HeadRotation, FRotator(), Delta, Speed);
	}
	else
	{
		HeadRotation = UKismetMathLibrary::RInterpTo(HeadRotation, ClampedRotation, Delta, Speed);
	}
}

void UPDAnimInstance::CalcAimOffset(const float Speed, const float Delta)
{
	// 캐릭터가 없으면 함수를 종료합니다.
	if (!Character)
		return;

	// 컨트롤러와 액터의 회전값을 가져옵니다.
	const FRotator ControlRotation = Character->GetControlRotation();
	const FRotator ActorRotation = Character->GetActorRotation();

	// 회전을 위한 새로운 회전값을 계산합니다.
	const float YawDifference = ControlRotation.Yaw - ActorRotation.Yaw;
	const float InvertedRoll = ControlRotation.Pitch * -1.0f;
	const FRotator NewRotation(0.0f, YawDifference, InvertedRoll);

	// 최대 회전 범위 내에서 회전을 제한합니다.
	const float ClampedYaw = FMath::ClampAngle(NewRotation.Yaw, -30, 45);
	const float ClampedRoll = FMath::ClampAngle(NewRotation.Roll, -45, 45);
	const FRotator ClampedRotation(0.0f, ClampedYaw, ClampedRoll);

	AimOffset = ClampedRotation;
}

void UPDAnimInstance::AnimNotify_FootStep_R()
{
	if(Character->GetFootStepComponent())
	{
		Character->GetFootStepComponent()->FootStep(ECharacterFoot::ECF_Right);
	}
}

void UPDAnimInstance::AnimNotify_FootStep_L()
{
	if(Character->GetFootStepComponent())
	{
		Character->GetFootStepComponent()->FootStep(ECharacterFoot::ECF_Left);
	}
}