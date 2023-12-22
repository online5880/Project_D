#include "TurnInPlaceComponent.h"
#include "Project_D/Character/PDCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Animation/AnimMontage.h"
#include "Project_D/Character/Animation/PDAnimInstance.h"
#include UE_INLINE_GENERATED_CPP_BY_NAME(TurnInPlaceComponent)

UTurnInPlaceComponent::UTurnInPlaceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTurnInPlaceComponent::BeginPlay()
{
	Super::BeginPlay();

	// 캐릭터와 애니메이션 인스턴스 설정
	InitializeCharacterAndAnimInstance();
}

void UTurnInPlaceComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 캐릭터의 회전 처리 로직
	ProcessCharacterRotation();
}

void UTurnInPlaceComponent::InitializeCharacterAndAnimInstance()
{
	if(OwnerCharacter == nullptr)
	{
		OwnerCharacter = Cast<APDCharacter>(GetOwner());
		if(OwnerCharacter)
		{
			AnimInstance = Cast<UPDAnimInstance>(OwnerCharacter->GetMesh()->GetAnimInstance()); 
		}
	}
}

void UTurnInPlaceComponent::ProcessCharacterRotation()
{
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
	if(FMath::Abs(YawDelta) > TurnThreshold)
	{
		if(FMath::Abs(YawDelta) > FullTurnThreshold)
		{
			PlayTurnMontageBasedOnYaw(YawDelta, "Right180", "Left180");
		}
		else
		{
			PlayTurnMontageBasedOnYaw(YawDelta, "Right90", "Left90");
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
		   OwnerCharacter->GetVelocity().Size2D() <= 0.f;
}

void UTurnInPlaceComponent::PlayTurnMontageBasedOnYaw(const float Yaw, const FString& RightTurn, const FString& LeftTurn)
{
	// Yaw 값에 따라 오른쪽 또는 왼쪽 회전 몽타주 재생
	const FString& SectionName = Yaw > 0 ? RightTurn : LeftTurn;

	// 몽타주 재생 및 회전 상태 설정
	if(StandTurnInPlaceMontage &&  CrouchTurnInPlaceMontage &&!bIsTurning)
	{
		FOnMontageEnded MontageEnded;
		MontageEnded.BindUObject(this,&UTurnInPlaceComponent::TurnMontageEnded);
		bIsTurning = true;
		
		if(OwnerCharacter->GetIsCrouching())
		{
			AnimInstance->Montage_Play(CrouchTurnInPlaceMontage, 1.f);
			AnimInstance->Montage_JumpToSection(*SectionName,CrouchTurnInPlaceMontage);
			AnimInstance->Montage_SetEndDelegate(MontageEnded,CrouchTurnInPlaceMontage);
		}
		else
		{
			AnimInstance->Montage_Play(StandTurnInPlaceMontage, 1.f);
			AnimInstance->Montage_JumpToSection(*SectionName,StandTurnInPlaceMontage);
			AnimInstance->Montage_SetEndDelegate(MontageEnded,StandTurnInPlaceMontage);
		}
	}
}

