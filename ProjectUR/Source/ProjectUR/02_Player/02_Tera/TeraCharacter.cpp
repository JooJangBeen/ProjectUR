// Fill out your copyright notice in the Description page of Project Settings.


#include "TeraCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Math.h"


// Sets default values
ATeraCharacter::ATeraCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetupDefault();
	LoadMeshAnimation();
	LoadEnhancedInput();
}

// Called when the game starts or when spawned
void ATeraCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocallyControlled())
	{
		APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

// Called every frame
void ATeraCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bIsTurn)
	{
		TurnTimer += DeltaSeconds;
		if (TurnTimer > 0.2f)
		{
			bIsTurn = false;
			TurnTimer = 0;
		}
	}

}

void ATeraCharacter::SetupDefault()
{
	JumpCurrentCount = 0;
	JumpMaxCount = 1;
	TurnTimer = 0;

	OldDirVector = FVector2d(0, 0);

	bIsTurn = false;
	IsAttacking = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	FollowCamera->SetRelativeLocation(FVector(70.f, 40.f, 75.f));

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -100.f), FRotator(0, -90.f, 0.f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
}

void ATeraCharacter::LoadMeshAnimation()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/02_Player/99_Resources/ParagonTerra/Characters/Heroes/Terra/Skins/GryphonKnight/Meshes/Terra_GryphonKnight.Terra_GryphonKnight'"));
	if (CharacterMeshRef.Object)
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstClassRef(TEXT("/Game/01_Blueprint/03_TerraAnimation/ABP_TerraBluePrint.ABP_TerraBluePrint_C"));
	if (AnimInstClassRef.Class)
		GetMesh()->SetAnimInstanceClass(AnimInstClassRef.Class);
}

void ATeraCharacter::LoadEnhancedInput()
{
	//Load Mapping Context
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/05_Input/04_Terra/IM_TerraDefault.IM_TerraDefault'"));
	if (InputMappingContextRef.Object)
		DefaultMappingContext = InputMappingContextRef.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>InputActionJumpRef(TEXT("/Script/EnhancedInput.InputAction'/Game/05_Input/04_Terra/InputAction/IA_TerraJump.IA_TerraJump'"));
	if (nullptr != InputActionJumpRef.Object)
		JumpAction = InputActionJumpRef.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/05_Input/04_Terra/InputAction/IA_TerraMove.IA_TerraMove'"));
	if (nullptr != InputActionMoveRef.Object)
		MoveAction = InputActionMoveRef.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionLookRef(TEXT("/Script/EnhancedInput.InputAction'/Game/05_Input/04_Terra/InputAction/IA_TerraLook.IA_TerraLook'"));
	if (nullptr != InputActionLookRef.Object)
		LookAction = InputActionLookRef.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionNormalAttackRef(TEXT("/Script/EnhancedInput.InputAction'/Game/05_Input/04_Terra/InputAction/IA_TerraAttack.IA_TerraAttack'"));
	if (nullptr != InputActionNormalAttackRef.Object)
		NormalAttackAction = InputActionNormalAttackRef.Object;
}

void ATeraCharacter::BindInputAction2Fuction(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATeraCharacter::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATeraCharacter::Look);
	EnhancedInputComponent->BindAction(NormalAttackAction, ETriggerEvent::Triggered, this, &ATeraCharacter::NormalAttack);
}

// Called to bind functionality to input
void ATeraCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	BindInputAction2Fuction(PlayerInputComponent);

}

void ATeraCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();


	FVector ForwardDirection = FVector(FollowCamera->GetForwardVector().X, FollowCamera->GetForwardVector().Y, 0).GetSafeNormal();
	FVector RightDirection = FVector(FollowCamera->GetRightVector().X, FollowCamera->GetRightVector().Y, 0).GetSafeNormal();

	MoveForwardInput = MovementVector.X;
	MoveRightInput = MovementVector.Y;

	FRotator ControlRot = GetControlRotation();

	FRotator YawRotation(0, NormalizeYaw(GetActorRotation().Yaw + CalculateYaw(ControlRot.Yaw, GetActorRotation().Yaw) * 0.2f), 0);

	// 카메라 방향으로 캐릭터 회전
	FQuat QuatRotation = FQuat(YawRotation);
	SetActorRotation(QuatRotation);

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);

	if (FVector2D::DotProduct(OldDirVector, MovementVector.GetSafeNormal()) < 0)
	{
		bIsTurn = true;
		TurnTimer = 0;
	}

	OldDirVector = MovementVector.GetSafeNormal();
}

void ATeraCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();


	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(-LookAxisVector.Y);
}

void ATeraCharacter::Jump()
{
	Super::Jump();
}

void ATeraCharacter::NormalAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Attack");
}

float ATeraCharacter::NormalizeYaw(float Yaw)
{
	while (Yaw >= 360.f) Yaw -= 360.0f;
	while (Yaw < 0) Yaw += 360.0f;
	return Yaw;
}

float ATeraCharacter::CalculateYaw(float DestYaw, float SourYaw)
{
	float NLDest = NormalizeYaw(DestYaw);
	float NLSour = NormalizeYaw(SourYaw);

	float Result = NLDest - NLSour;
	float a, b;
	a = NLDest - 360.f - NLSour;
	b = NLDest + 360.f - NLSour;

	if (fabsf(Result) > 180.f)
	{
		if (fabsf(Result) < fabsf(a))
		{
			if (fabsf(Result) < fabsf(b))
				return Result;
			else
				return b;
		}
		else
		{

			if (fabsf(a) < fabsf(b))
				return a;
			else
				return b;
		}
	}


	return Result;
}

