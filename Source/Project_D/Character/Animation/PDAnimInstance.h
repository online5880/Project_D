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

private:
	// 캐릭터 클래스
	UPROPERTY(BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<APDCharacter> Character;

	// 무브먼트 컴포넌트
	UPROPERTY(BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UCharacterMovementComponent> MovementComponent;

	// 속도
	UPROPERTY(BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
		float GroundSpeed;

	// 방향
	UPROPERTY(BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
		float Direction;

	// 움직이고 있는지
	UPROPERTY(BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
		bool ShouldMove;

	// 떨어지고 있는지
	UPROPERTY(BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
		bool IsFalling;

	// Right Input Value
	UPROPERTY(BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
		float RightInputValue;

	// Forward Input Value
	UPROPERTY(BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
		float ForwardInputValue;
};