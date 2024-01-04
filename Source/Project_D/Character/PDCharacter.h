#pragma once

#include "../../../../../Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "GameFramework/Character.h"
#include "Project_D/Interface/InteractInterface.h"
#include "PDCharacter.generated.h"

class UFootStepComponent;
class UJumpComponent;
class UTurnInPlaceComponent;
class UInputAction;
class UInputMappingContext;
class UCameraComponent;
class USpringArmComponent;

UENUM(BlueprintType)
enum class ECharacterCombatState : uint8
{
	ECCS_Unarmed UMETA(DisplayName = "Unarmed"),
	ECCS_Rifle UMETA(DisplayName = "Rifle"),
	ECCS_Pistol UMETA(DisplayName = "Pistol"),
	ECCS_DefaultMAX UMETA(DisplayName = "MAX")
};

UCLASS()
class PROJECT_D_API APDCharacter : public ACharacter, public IInteractInterface
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

	// IInteract Interface
	virtual void Interact() override;
	virtual void PickupWeapon(ABaseWeapon* NewWeapon, const FName& SocketName) override;
	
	/**
	 * member method
	 */
	void Move(const FInputActionValue& Value);
	void MoveComplete(const FInputActionValue& Value);
	void Walk(const FInputActionValue& Value);
	void Crouching(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Interaction(const FInputActionValue& Value);
	void Attack(const FInputActionValue& Value);
	void Aimimg(const FInputActionValue& Value);

	// 카메라 회전을 부드럽게 해준다.
	void SmoothCameraRotation(float DeltaTime);
	// Aiming 카메라
	void SmoothAimCamera(const float DeltaTime);

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
	
	// 상호작용 액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InteractAction;

	// 공격 액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> AttackInputAction;

	// Aim 액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> AimInputAction;
	
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

	// 조준 중인지
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bIsAiming;

#pragma region Weapon
	// 장착중인 무기
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ABaseWeapon> EquippedWeapon;

#pragma region Object
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AActor> OverlappedActor;

#pragma region Enum
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Combat", meta = (AllowPrivateAccess = "true"))
	ECharacterCombatState CombatState;

public:
#pragma region INLINE_FUNCTION
	FORCEINLINE float					GetForwardInputValue() const { return ForwardInputValue; }
	FORCEINLINE float					GetRightInputValue() const { return RightInputValue; }
	FORCEINLINE bool					GetIsCrouching() const { return bIsCrouching; }
	FORCEINLINE UFootStepComponent*		GetFootStepComponent() const {return FootStepComponent;}
	FORCEINLINE AActor*					GetOverlappedActor() const {return OverlappedActor;}
	FORCEINLINE void					SetOverlappedActor(AActor* Actor) {OverlappedActor = Actor;}
	FORCEINLINE ECharacterCombatState	GetCharacterCombatState() const {return CombatState;}
	FORCEINLINE void					SetCharacterCombatState(const ECharacterCombatState State) {CombatState = State;}
	FORCEINLINE bool					GetIsAiming() const {return bIsAiming;}
	FORCEINLINE ABaseWeapon*			GetEquippedWeapon() const {return EquippedWeapon;}
};