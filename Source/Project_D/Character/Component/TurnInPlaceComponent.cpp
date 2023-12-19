#include "TurnInPlaceComponent.h"
#include "Project_D/Character/PDCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Animation/AnimMontage.h"
#include "Project_D/Character/Animation/PDAnimInstance.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(TurnInPlaceComponent)

// 상수 정의
constexpr float TurnThreshold = 45.f;
constexpr float FullTurnThreshold = 135.f;

UTurnInPlaceComponent::UTurnInPlaceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTurnInPlaceComponent::BeginPlay()
{
	Super::BeginPlay();

	if(OwnerCharacter == nullptr)
	{
		OwnerCharacter = Cast<APDCharacter>(GetOwner());
		if(OwnerCharacter)
		{
			AnimInstance = Cast<UPDAnimInstance>(OwnerCharacter->GetMesh()->GetAnimInstance()); 
			if(AnimInstance)
			{
				AnimInstance->OnMontageEnded.AddDynamic(this,&ThisClass::UTurnInPlaceComponent::TurnMontageEnded);
			}
		}
	}
}

void UTurnInPlaceComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(OwnerCharacter)
	{
		YawDelta = UKismetMathLibrary::NormalizedDeltaRotator(OwnerCharacter->GetActorRotation(),OwnerCharacter->GetBaseAimRotation()).Yaw * -1;
		TurnInPlace();
	}
}

void UTurnInPlaceComponent::TurnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	bIsTurning = false;
}

void UTurnInPlaceComponent::DetermineTurnAction()
{
	// YawDelta를 이용하여 적절한 회전 액션 결정
	if(abs(YawDelta) > TurnThreshold)
	{
		if(abs(YawDelta) > FullTurnThreshold)
		{
			PlayTurnMontageBasedOnYaw(YawDelta, "TurnRight180", "TurnLeft180");
		}
		else
		{
			PlayTurnMontageBasedOnYaw(YawDelta, "TurnRight90", "TurnLeft90");
		}
	}
}

void UTurnInPlaceComponent::TurnInPlace()
{
	// 캐릭터가 회전할 수 있는 조건을 확인
	if(!IsValid(OwnerCharacter) || !CanTurnInPlace()) 
		return;
	
	// 회전 액션 결정 및 실행
	DetermineTurnAction();
}

bool UTurnInPlaceComponent::CanTurnInPlace() const
{
	// 캐릭터가 떨어지지 않고, 속도가 0 이하이며, 웅크리지 않은 상태인지 확인
	return !OwnerCharacter->GetCharacterMovement()->IsFalling() &&
		   OwnerCharacter->GetVelocity().Size2D() <= 0.f &&
		   !OwnerCharacter->GetIsCrouching();
}

void UTurnInPlaceComponent::PlayTurnMontageBasedOnYaw(const float Yaw, const FString& RightTurn, const FString& LeftTurn)
{
	// Yaw 값에 따라 오른쪽 또는 왼쪽 회전 몽타주 재생
	const FString& MontageName = Yaw > 0 ? RightTurn : LeftTurn;
	UAnimMontage* MontageToPlay = TurnMontage.Find(MontageName)->Get();

	// 몽타주 재생 및 회전 상태 설정
	if(MontageToPlay && !bIsTurning)
	{
		bIsTurning = true;
		AnimInstance->Montage_Play(MontageToPlay, 1.f);
	}
}

void UTurnInPlaceComponent::ClearMotion() const
{
	if(OwnerCharacter->IsPlayingRootMotion())
	{
		OwnerCharacter->StopAnimMontage(OwnerCharacter->GetCurrentMontage());
	}
}

