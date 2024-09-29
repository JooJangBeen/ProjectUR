// Fill out your copyright notice in the Description page of Project Settings.


#include "TeraCharacter.h"
#include "InputMappingContext.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


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

	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
}

// Called every frame
void ATeraCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATeraCharacter::SetupDefault()
{
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

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

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstClassRef(TEXT("/Game/02_Player/99_Resources/ParagonTerra/Characters/Heroes/Terra/Terra_AnimBlueprint.Terra_AnimBlueprint_C"));
	if (AnimInstClassRef.Class)
		GetMesh()->SetAnimInstanceClass(AnimInstClassRef.Class);
}

void ATeraCharacter::LoadEnhancedInput()
{
	//Load Mapping Context
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/05_Input/01_Terra/IM_TerraDefault.IM_TerraDefault'"));
	if (InputMappingContextRef.Object)
		DefaultMappingContext = InputMappingContextRef.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>InputActionJumpRef(TEXT("/Script/EnhancedInput.InputAction'/Game/05_Input/01_Terra/InputAction/IA_TerraJump.IA_TerraJump'"));
	if (nullptr != InputActionJumpRef.Object)
		JumpAction = InputActionJumpRef.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/05_Input/01_Terra/InputAction/IA_TerraMove.IA_TerraMove'"));
	if (nullptr != InputActionMoveRef.Object)
		MoveAction = InputActionMoveRef.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionLookRef(TEXT("/Script/EnhancedInput.InputAction'/Game/05_Input/01_Terra/InputAction/IA_TerraLook.IA_TerraLook'"));
	if (nullptr != InputActionLookRef.Object)
		LookAction = InputActionLookRef.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionNormalAttackRef(TEXT("/Script/EnhancedInput.InputAction'/Game/05_Input/01_Terra/InputAction/IA_TerraAttack.IA_TerraAttack'"));
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

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.X);
	AddMovementInput(RightDirection, MovementVector.Y);
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

