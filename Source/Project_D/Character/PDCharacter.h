#pragma once

#include "../../../../../Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "GameFramework/Character.h"
#include "PDCharacter.generated.h"

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

	/**
	 * member method
	 */
	void Move(const FInputActionValue& Value);
	void MoveComplete(const FInputActionValue& Value);
	void Walk(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void SmoothCameraRotation(float DeltaTime);

private:
#pragma region Component
	// 스프링암
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<USpringArmComponent> SpringArmComponent;

	// 카메라
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UCameraComponent> CameraComponent;

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

public:
	FORCEINLINE float GetForwardInputValue() const { return ForwardInputValue; }
	FORCEINLINE float GetRightInputValue() const { return RightInputValue; }
};