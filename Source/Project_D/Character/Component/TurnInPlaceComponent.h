﻿#pragma once

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
	// 캐릭터와 애니메이션 인스턴스 설정
	void InitializeCharacterAndAnimInstance();
	
	// 캐릭터의 회전 처리 로직
	void ProcessCharacterRotation();

	// 회전 Montage Ended Delegate
	UFUNCTION()
	void TurnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	// 캐릭터 회전 동작을 결정하는 함수
	void DetermineTurnAction();
	
	// 캐릭터가 회전할 수 있는지 확인 후 회전 처리
	void TurnInPlace();
	
	// 캐릭터가 회전할 수 있는 조건을 확인하는 함수
	bool CanTurnInPlace() const;

	// Yaw 값에 따라 적절한 회전 몽타주를 재생하는 함수
	void PlayTurnMontageBasedOnYaw(float Yaw, const FString& RightTurn, const FString& LeftTurn);
private:
	// 캐릭터
	UPROPERTY()
	TObjectPtr<APDCharacter> OwnerCharacter;

	// 애님 인스턴스
	UPROPERTY()
	TObjectPtr<UPDAnimInstance> AnimInstance;

	// 회전 중인지
	UPROPERTY()
	bool bIsTurning = false;

	// 서있을 때 회전 몽타주
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category= "TurnInPlace", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> StandTurnInPlaceMontage;

	// 앉아 있을 때 회전 몽타주
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category= "TurnInPlace", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> CrouchTurnInPlaceMontage;
	
	// 총 들고 있을 때 회전 몽타주
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category= "TurnInPlace", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> RifleTurnInPlaceMontage;
	
	double YawDelta;

	// 회전 임계값
	UPROPERTY(EditAnywhere,BlueprintReadOnly ,Category = "TurnInPlace", meta = (AllowPrivateAccess = "true"))
	float TurnThreshold = 45.f;

	// 최대 회전 임계값
	UPROPERTY(EditAnywhere,BlueprintReadOnly ,Category = "TurnInPlace", meta = (AllowPrivateAccess = "true"))
	float FullTurnThreshold = 135.f;

public:
	// bIsTurning Getter
	FORCEINLINE bool GetIsTurning() const {return bIsTurning;}
};
