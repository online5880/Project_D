#pragma once

#include "../../../../../Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "GameFramework/Character.h"
#include "PDCharacter.generated.h"

class UFootStepComponent;
class UJumpComponent;
class UTurnInPlaceComponent;
class UInputAction;
class UInputMappingContext;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class PROJECT_D_API APDCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APDCharacter();

	/**
	 * Enhanced Action Mapping
	 */
	void MappingContext() const;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void Jump() override;
	/**
	 * member method
	 */
	void Move(const FInputActionValue& Value);
	void MoveComplete(const FInputActionValue& Value);
	void Walk(const FInputActionValue& Value);
	void Crouching(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	// 카메라 회전을 부드럽게 해준다.
	void SmoothCameraRotation(float DeltaTime);

private:
#pragma region Component
	// 스프링암
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent>		SpringArmComponent;

	// 카메라
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent>		CameraComponent;

	// TurnInPlace Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTurnInPlaceComponent>	TurnInPlaceComponent;

	// Jump Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UJumpComponent>			JumpComponent;

	// Foot Step Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UFootStepComponent>		FootStepComponent;
	
#pragma region InputAction
	// 맵핑 콘텍스트
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	// 점프 액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	// 무브 액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	// 카메라 움직임 액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

	// 걷기 액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> WalkAction;

	// 걷기 액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> CrouchAction;

#pragma region Movement Variables
	// 움직임 값 - X
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float RightInputValue;

	// 움직임 값 - Y
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float ForwardInputValue;

	// 걷는 중인지
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bIsWalk;

	// 앉아 있는지
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bIsCrouching;

public:
	FORCEINLINE float				GetForwardInputValue() const { return ForwardInputValue; }
	FORCEINLINE float				GetRightInputValue() const { return RightInputValue; }
	FORCEINLINE bool				GetIsCrouching() const { return bIsCrouching; }
	FORCEINLINE UFootStepComponent* GetFootStepComponent() const {return FootStepComponent;}
};