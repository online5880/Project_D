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
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

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

	// 달리기 액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UInputAction> SprintAction;

	// 앉기 액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UInputAction> CrouchAction;
};