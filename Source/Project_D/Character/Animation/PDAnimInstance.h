#pragma once

#include "Animation/AnimInstance.h"
#include "PDAnimInstance.generated.h"

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
	// 제자리 회전
	void TurnInPlace();

	// 머리 회전
	void CalcHeadRotation(const float MaxLeftRight, const float MaxUpDown, const float Speed, const float Delta);

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

#pragma region TurnInPlace
	float MovementOffsetYaw;
	float LastMovementOffsetYaw;
	
	// 현재 프레임의 Yaw
	float CharacterYaw = 0.f;
	// 이전 프레임의 Yaw
	float CharacterYawLastFrame = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float RootYawOffset = 0.f;;

	// 현재 프레임의 회전 커브 값
	float RotationCurve;

	// 마지막 프레임의 회전 커브 값
	float RotationCurveLastFrame;

#pragma region HeadRotation
	// 머리 회전 값(transform modify bone - head)
	UPROPERTY(BlueprintReadOnly,Category = "Movement",meta = (AllowPrivateAccess = "true"))
	FRotator HeadRotation;
	
};