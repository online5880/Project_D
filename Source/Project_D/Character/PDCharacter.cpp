#include "PDCharacter.h"

#include "../../../../../Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "../../../../../Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(PDCharacter)

APDCharacter::APDCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->TargetArmLength = 400.f;
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	bIsWalk = false;
}

void APDCharacter::MappingContext() const
{
	if(const APlayerController* PC = Cast<APlayerController>(Controller))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			if(DefaultMappingContext)
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
}

void APDCharacter::BeginPlay()
{
	Super::BeginPlay();

	MappingContext();
}

void APDCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	SmoothCameraRotation(DeltaSeconds);
}

void APDCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ThisClass::MoveComplete);
		EnhancedInputComponent->BindAction(WalkAction, ETriggerEvent::Triggered, this, &ThisClass::Walk);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
	}
}

void APDCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if(Controller != nullptr)
	{
		if(bIsWalk)
		{
			ForwardInputValue = MovementVector.Y;
			RightInputValue = MovementVector.X;
		}
		else
		{
			ForwardInputValue = MovementVector.Y*2;
			RightInputValue = MovementVector.X*2;
		}
		
	}
}

void APDCharacter::MoveComplete(const FInputActionValue& Value)
{
	RightInputValue = 0.f;
	ForwardInputValue = 0.f;
}

void APDCharacter::Walk(const FInputActionValue& Value)
{
	bIsWalk = Value.Get<bool>();
}

void APDCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APDCharacter::SmoothCameraRotation(float DeltaTime)
{
	if (RightInputValue != 0.f || ForwardInputValue != 0.f)
	{
		const FRotator InterpRot = UKismetMathLibrary::RInterpTo(GetActorRotation(), GetControlRotation(), DeltaTime, 6.f);
		SetActorRotation(FRotator(0.f, InterpRot.Yaw, 0.f));
	}
}