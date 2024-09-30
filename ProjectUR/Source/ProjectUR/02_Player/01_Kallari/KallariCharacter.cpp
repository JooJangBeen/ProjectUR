// Fill out your copyright notice in the Description page of Project Settings.


#include "KallariCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AKallariCharacter::AKallariCharacter()
{
	SetupDefault();
	LoadMeshAnimation();
	LoadEnhancedInput();
	InitializeCardData(ECharacterType::Kallari);
}

void AKallariCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	BindInputAction2Fuction(PlayerInputComponent);
}

void AKallariCharacter::BeginPlay()
{
	Super::BeginPlay();


	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
}

void AKallariCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void AKallariCharacter::SetupDefault()
{
	JumpCurrentCount = 0;
	JumpMaxCount = 2;
	
	OldDirVector = FVector2d(0, 0);

	bIsTurn = false;
	IsAttacking = false;
	bPressAttack = false;

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	FollowCamera->SetRelativeLocation(FVector(-20.f, 40.f, 70.f));

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -100.f), FRotator(0, -90.f, 0.f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName((TEXT("CharacterMesh")));
}

void AKallariCharacter::LoadMeshAnimation()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/02_Player/99_Resources/ParagonKallari/Characters/Heroes/Kallari/Skins/Tough/Meshes/Kallari_Tough.Kallari_Tough'"));
	if (CharacterMeshRef.Object)
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstClassRef(TEXT("/Game/02_Player/01_Kallari/ABP_Kallari.ABP_Kallari_C"));
	//static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstClassRef(TEXT("/Game/02_Player/99_Resources/ParagonKallari/Characters/Heroes/Kallari/Kallari_AnimBlueprint.Kallari_AnimBlueprint_C"));
	if (AnimInstClassRef.Class)
		GetMesh()->SetAnimInstanceClass(AnimInstClassRef.Class);
}

void AKallariCharacter::LoadEnhancedInput()
{
	//Load Mapping Context
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/05_Input/01_Kallari/IM_KallariDefault.IM_KallariDefault'"));
	if (InputMappingContextRef.Object)
		DefaultMappingContext = InputMappingContextRef.Object;

	//Load Input Action
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionJumpRef(TEXT("/Script/EnhancedInput.InputAction'/Game/05_Input/01_Kallari/InputAction/IA_KallariJump.IA_KallariJump'"));
	if (nullptr != InputActionJumpRef.Object)
		JumpAction = InputActionJumpRef.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/05_Input/01_Kallari/InputAction/IA_KallariMove.IA_KallariMove'"));
	if (nullptr != InputActionMoveRef.Object)
		MoveAction = InputActionMoveRef.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionLookRef(TEXT("/Script/EnhancedInput.InputAction'/Game/05_Input/01_Kallari/InputAction/IA_KallariLook.IA_KallariLook'"));
	if (nullptr != InputActionLookRef.Object)
		LookAction = InputActionLookRef.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionSkillEDRef(TEXT("/Script/EnhancedInput.InputAction'/Game/05_Input/01_Kallari/InputAction/IA_KallariSkillED.IA_KallariSkillED'"));
	if (nullptr != InputActionSkillEDRef.Object)
		SkillEDAction = InputActionSkillEDRef.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionSkillSSBRef(TEXT("/Script/EnhancedInput.InputAction'/Game/05_Input/01_Kallari/InputAction/IA_KallariSkillSSB.IA_KallariSkillSSB'"));
	if (nullptr != InputActionSkillSSBRef.Object)
		SkillSSBAction = InputActionSkillSSBRef.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionSkillAHARef(TEXT("/Script/EnhancedInput.InputAction'/Game/05_Input/01_Kallari/InputAction/IA_KallariSkillAHA.IA_KallariSkillAHA'"));
	if (nullptr != InputActionSkillAHARef.Object)
		SkillAHAAction = InputActionSkillAHARef.Object;

}

void AKallariCharacter::BindInputAction2Fuction(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AKallariCharacter::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AKallariCharacter::Look);
	EnhancedInputComponent->BindAction(SkillEDAction, ETriggerEvent::Triggered, this, &AKallariCharacter::Skill_ED);
	EnhancedInputComponent->BindAction(SkillSSBAction, ETriggerEvent::Triggered, this, &AKallariCharacter::Skill_SSB);
	EnhancedInputComponent->BindAction(SkillAHAAction, ETriggerEvent::Triggered, this, &AKallariCharacter::Skill_AHA);
}

void AKallariCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	MoveForwardInput = MovementVector.Y;
	MoveRightInput = MovementVector.X;


	AddMovementInput(ForwardDirection, MovementVector.X);
	AddMovementInput(RightDirection, MovementVector.Y);



	bIsTurn = ( FVector2D::DotProduct(OldDirVector, MovementVector.GetSafeNormal()) < 0 )? true: false;

	OldDirVector = MovementVector.GetSafeNormal();
}

void AKallariCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(-LookAxisVector.Y);
}
void AKallariCharacter::Skill_ED(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Activated Skill Eclipse Dagger");
}

void AKallariCharacter::Skill_SSB(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Activated Skill Shadow step/Blink");
}

void AKallariCharacter::Skill_AHA(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Activated Skill Annihilation");
}
