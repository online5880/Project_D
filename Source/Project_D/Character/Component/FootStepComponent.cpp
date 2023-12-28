#include "FootStepComponent.h"
#include "MetasoundSource.h"
#include "Components/AudioComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include UE_INLINE_GENERATED_CPP_BY_NAME(FootStepComponent)

UFootStepComponent::UFootStepComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	// 오디오 컴포넌트 초기화
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	AudioComponent->bAutoActivate = false;
}

void UFootStepComponent::BeginPlay()
{
	Super::BeginPlay();

	if(Character == nullptr)
	{
		Character = Cast<ACharacter>(GetOwner());
	}
}

void UFootStepComponent::FootStep(const ECharacterFoot Foot) const
{
	// 발소리 처리에 대한 분기
	switch (Foot)
	{
	case ECharacterFoot::ECF_Left:
		FootStepSphereTrace(ECharacterFoot::ECF_Left);
		break;
	case ECharacterFoot::ECF_Right:
		FootStepSphereTrace(ECharacterFoot::ECF_Right);
		break;
	case ECharacterFoot::ECF_Land:
		// TODO 현재 미구현
		break;
	case ECharacterFoot::ECF_DefaultMAX: break;
	default: ;
	}
}

FName UFootStepComponent::GetFootBoneName(const ECharacterFoot Foot) const
{
	// 발 본 이름 반환
	switch (Foot)
	{
	case ECharacterFoot::ECF_Left:
		return FootLeftBoneName;
	case ECharacterFoot::ECF_Right:
		return FootRightBoneName;
	default:
		return NAME_None;
	}
}

void UFootStepComponent::FootStepSphereTrace(const ECharacterFoot Foot) const
{
	// 발의 시작 위치 결정
	FVector Start = Character ? Character->GetMesh()->GetSocketLocation(GetFootBoneName(Foot)) : FVector::ZeroVector;
	const FVector End = Start - FVector(0.f, 0.f, TraceOffset);
    
	FHitResult HitResult;
	TArray<AActor*> IgnoreActors;
	IgnoreActors.AddUnique(GetOwner());
        
	// Sphere Trace 실행
	UKismetSystemLibrary::SphereTraceSingle(
		GetWorld(),
		Start,
		End,
		TraceRadius,
		TraceTypeQuery1,
		false,
		IgnoreActors,
		bDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None,
		HitResult,
		true);

	// 히트가 발생했을 경우 사운드 재생
	if(HitResult.bBlockingHit && HitResult.PhysMaterial.IsValid())
	{
		const EPhysicalSurface Surface = HitResult.PhysMaterial->SurfaceType.GetValue();
		FFootSoundStruct FootSoundStruct;
		if(GetFootSound(Surface, FootSoundStruct))
		{
			PlayFootStepSound(FootSoundStruct, Foot);
		}
	}
}

bool UFootStepComponent::GetFootSound(const EPhysicalSurface Surface, FFootSoundStruct& FootSoundStruct) const
{
	// 표면 유형에 따른 사운드 큐를 찾음
	if(FootSoundMap.Contains(Surface))
	{
		FootSoundStruct = FootSoundMap[Surface];
		return true;
	}
	return false;
}

void UFootStepComponent::PlayFootStepSound(const FFootSoundStruct& FootSoundStruct, const ECharacterFoot Foot) const
{
	if(AudioComponent)
	{
		UMetaSoundSource* PlaySoundCue = nullptr;
		switch (Foot)
		{
		case ECharacterFoot::ECF_Left:
			PlaySoundCue = FootSoundStruct.LeftSoundCue;
			break;
		case ECharacterFoot::ECF_Right:
			PlaySoundCue = FootSoundStruct.RightSoundCue;
			break;
		case ECharacterFoot::ECF_Land:
			PlaySoundCue = FootSoundStruct.LandSoundCue;
			break;
		case ECharacterFoot::ECF_DefaultMAX:
			break;
		default: ;
		}
		if(PlaySoundCue && bEnableSound)
		{
			AudioComponent->Stop();
			AudioComponent->SetSound(PlaySoundCue);
			AudioComponent->Play();
		}
	}
}

