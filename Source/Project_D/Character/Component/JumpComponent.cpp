#include "JumpComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Project_D/Character/PDCharacter.h"
#include "Project_D/Character/Animation/PDAnimInstance.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(JumpComponent)

UJumpComponent::UJumpComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UJumpComponent::BeginPlay()
{
	Super::BeginPlay();

	// 캐릭터와 애니메이션 인스턴스 설정
	InitializeCharacterAndAnimInstance();
}

void UJumpComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UJumpComponent::InitializeCharacterAndAnimInstance()
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

void UJumpComponent::ChangeMovementModeAfterJump(const EMovementMode NewMode) const
{
	if (UCharacterMovementComponent* MovementComponent = OwnerCharacter->GetCharacterMovement())
	{
		MovementComponent->SetMovementMode(NewMode);
	}
}

bool UJumpComponent::CanJump() const
{
	const UCharacterMovementComponent* MovementComponent = OwnerCharacter->GetCharacterMovement();
	return MovementComponent && !MovementComponent->IsFalling() && MovementComponent->MovementMode != MOVE_Flying;
}


void UJumpComponent::JumpEnded(UAnimMontage* Montage, bool bInterrupted)
{
	// 몽타주 종료 시 무브먼트 모드 조정
	ChangeMovementModeAfterJump(MOVE_Walking);
}

void UJumpComponent::Jump(const float Speed)
{
	if (!CanJump()) return;

	const FString MontageName = DetermineJumpMontage(Speed);
	if (MontageName.IsEmpty()) return;

	UAnimMontage* MontageToPlay = JumpMontages.Find(MontageName)->Get();
	PlayJumpMontage(MontageToPlay);
}

void UJumpComponent::PlayJumpMontage(UAnimMontage* MontageToPlay)
{
	ChangeMovementModeAfterJump(MOVE_Flying);

	FOnMontageEnded MontageEnded;
	MontageEnded.BindUObject(this, &UJumpComponent::JumpEnded);
	AnimInstance->Montage_Play(MontageToPlay, 1.f);
	AnimInstance->Montage_SetEndDelegate(MontageEnded, MontageToPlay);
}

FString UJumpComponent::DetermineJumpMontage(const float Speed) const
{
	if(Speed < 50.f) return "InPlace";
	if(Speed < 150.f) return "Walk";
	if(Speed > 300.f) return "Run";
	return "";
}

