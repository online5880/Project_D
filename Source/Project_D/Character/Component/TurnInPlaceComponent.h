#pragma once

#include "Components/ActorComponent.h"
#include "TurnInPlaceComponent.generated.h"


class UPDAnimInstance;
class APDCharacter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_D_API UTurnInPlaceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTurnInPlaceComponent();

	virtual void BeginPlay() override;
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;
protected:
	UFUNCTION()
	void TurnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	void DetermineTurnAction();
	
	void TurnInPlace();

	bool CanTurnInPlace() const;

	void PlayTurnMontageBasedOnYaw(float Yaw, const FString& RightTurn, const FString& LeftTurn);

	void ClearMotion() const;

private:
	// 캐릭터
	UPROPERTY()
	TObjectPtr<APDCharacter> OwnerCharacter;

	// 애님 인스턴스
	UPROPERTY()
	TObjectPtr<UPDAnimInstance> AnimInstance;

	// 돌고 있는지
	UPROPERTY()
	bool bIsTurning = false;

	/**
	 * @brief Montage Map (Key:이름, Value:Montage)
	 */
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category= "TurnInPlace", meta = (AllowPrivateAccess = "true"))
	TMap<FString,TObjectPtr<UAnimMontage>> TurnMontage;
	
	double YawDelta;
};
