#pragma once

#include "Components/ActorComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "FootStepComponent.generated.h"

class UMetaSoundSource;
class UAudioComponent;
class USoundCue;
class ACharacter;

UENUM(BlueprintType)
enum class ECharacterFoot : uint8
{
	ECF_Left UMETA(DisplayName = "Left"),
	ECF_Right UMETA(DisplayName = "Right"),
	ECF_Land UMETA(DisplayName = "Land"),
	ECF_DefaultMAX UMETA(DisplayName = "MAX")
};

USTRUCT(BlueprintType)
struct FFootSoundStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMetaSoundSource> LeftSoundCue;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMetaSoundSource> RightSoundCue;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UMetaSoundSource> LandSoundCue;
};

class USoundCue;
/**
 * Foot Step Component
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_D_API UFootStepComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFootStepComponent();
	virtual void BeginPlay() override;
	
	// Foot Step(Sound, Effect...)
	void FootStep(const ECharacterFoot Foot) const;
protected:
	// 발 본 이름 반환
	FName GetFootBoneName(const ECharacterFoot Foot) const;
	// Sphere Trace
	void FootStepSphereTrace(const ECharacterFoot Foot) const;

#pragma region Sound
	// 표면 유형에 따른 사운드 큐를 찾음 
	bool GetFootSound(const EPhysicalSurface Surface, FFootSoundStruct& FootSoundStruct) const;
	// 적절한 사운드 큐 재생
	void PlayFootStepSound(const FFootSoundStruct& FootSoundStruct,ECharacterFoot Foot) const;
	
private:
	// 오디오 컴포넌트
	UPROPERTY()
	TObjectPtr<UAudioComponent> AudioComponent;
	
	// Owner Character
	UPROPERTY()
	TObjectPtr<ACharacter> Character;

	// Sound Map - key:PhysicalSurface, value:SoundCue
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category= "Sound", meta = (AllowPrivateAccess = "true"));
	TMap<TEnumAsByte<EPhysicalSurface>, FFootSoundStruct> FootSoundMap;

	// 오른쪽 발 Bone 이름
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category= "Sound", meta = (AllowPrivateAccess = "true"))
	FName FootRightBoneName;

	// 왼쪽 발 Bone 이름
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category= "Sound", meta = (AllowPrivateAccess = "true"))
	FName FootLeftBoneName;

	// Trace Offset(-z value)
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category= "Sound", meta = (AllowPrivateAccess = "true"))
	float TraceOffset = 30.f;

	// Trace Radius
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category= "Sound", meta = (AllowPrivateAccess = "true"))
	float TraceRadius = 3.f;

	// 디버그
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Debug", meta = (AllowPrivateAccess = "true"))
	bool bDebug;
};
