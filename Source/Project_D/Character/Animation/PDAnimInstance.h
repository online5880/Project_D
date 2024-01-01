#pragma once

#include "Animation/AnimInstance.h"
#include "PDAnimInstance.generated.h"

enum class ECharacterCombatState : uint8;
class UCharacterMovementComponent;
class APDCharacter;

UCLASS()
class PROJECT_D_API UPDAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPDAnimInstance();

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	/**
	 * member method
	 */

	// 머리 회전
	void CalcHeadRotation(const float MaxLeftRight, const float MaxUpDown, const float Speed, const float Delta);

	// Aim Offset
	void CalcAimOffset(const float Speed, const float Delta);

	// 애님노티파이 - FootStep Right
	UFUNCTION()
	void AnimNotify_FootStep_R();

	// 애님노티파이 - FootStep Left
	UFUNCTION()
	void AnimNotify_FootStep_L();
private:
	// 캐릭터 클래스
	UPROPERTY(BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<APDCharacter> Character;

	// 무브먼트 컴포넌트
	UPROPERTY(BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCharacterMovementComponent> MovementComponent;

	// 속도
	UPROPERTY(BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	float GroundSpeed = 0.f;

	// 방향
	UPROPERTY(BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	float Direction = 0.f;

	// 움직이고 있는지
	UPROPERTY(BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	bool bShouldMove = false;

	// 떨어지고 있는지
	UPROPERTY(BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	bool bIsFalling = false;

	// 떨어지고 있는지
	UPROPERTY(BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	bool bIsCrouching = false;

	// Right Input Value
	UPROPERTY(BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	float RightInputValue = 0.f;

	// Forward Input Value
	UPROPERTY(BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	float ForwardInputValue = 0.f;

#pragma region HeadRotation
	// 머리 회전 값(transform modify bone - head)
	UPROPERTY(BlueprintReadOnly,Category = "Movement",meta = (AllowPrivateAccess = "true"))
	FRotator HeadRotation;

	// Aim Offset
	UPROPERTY(BlueprintReadOnly,Category = "Movement",meta = (AllowPrivateAccess = "true"))
	FRotator AimOffset;

#pragma region ENUM
	UPROPERTY(BlueprintReadOnly,Category = "Enum",meta = (AllowPrivateAccess = "true"))
	ECharacterCombatState CombatState;
	
};