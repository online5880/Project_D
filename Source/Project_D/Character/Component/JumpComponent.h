// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "JumpComponent.generated.h"

class UPDAnimInstance;
class APDCharacter;
class UAnimMontage;

/**
 * 점프 컴포넌트
 * TODO 추후 변경 또는 삭제
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_D_API UJumpComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UJumpComponent();
	
	virtual void BeginPlay() override;
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
								   FActorComponentTickFunction* ThisTickFunction) override;
	
	// 캐릭터와 애니메이션 인스턴스 설정
	void InitializeCharacterAndAnimInstance();
	
	void ChangeMovementModeAfterJump(EMovementMode NewMode) const;

	bool CanJump() const;
	
	UFUNCTION()
	void JumpEnded(UAnimMontage* Montage, bool bInterrupted);
	
	void Jump(const float Speed);

	void PlayJumpMontage(UAnimMontage* MontageToPlay);

	FString DetermineJumpMontage(const float Speed) const;

	// 캐릭터
	UPROPERTY()
	TObjectPtr<APDCharacter> OwnerCharacter;

	// 애님 인스턴스
	UPROPERTY()
	TObjectPtr<UPDAnimInstance> AnimInstance;

private:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category= "JumpComponent|Montage", meta = (AllowPrivateAccess = "true"))
	TMap<FString, TObjectPtr<UAnimMontage>> JumpMontages;
};
