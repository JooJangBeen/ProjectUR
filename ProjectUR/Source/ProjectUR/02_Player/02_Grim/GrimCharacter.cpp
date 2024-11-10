// Fill out your copyright notice in the Description page of Project Settings.


#include "GrimCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/Engine.h"

AGrimCharacter::AGrimCharacter()
{
	SetupDefault();
	LoadMeshAnimation();
	LoadEnhancedInput();
	InitializeCardData(ECharacterType::Grim);

	GrimAttribute = CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("AbilitySystemComponent"));
}

void AGrimCharacter::BeginPlay()
{
	Super::BeginPlay();


	//APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	//if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	//	Subsystem->AddMappingContext(DefaultMappingContext, 0);
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController && PlayerController->IsLocalPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AGrimCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (HasAuthority())
	{
		// 현재 플레이어 컨트롤러 가져오기
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			// 예: 'F' 키가 눌렸는지 확인
			if (PlayerController->IsInputKeyDown(EKeys::F))
			{
				//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Eclipse Dagger Input : %f, %f"), MouseInput.X, MouseInput.Y));
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Input F"));

				ENetworkType = EGrimNetworkType::A;
			}

			// 예: 'G' 키가 방금 눌렸는지 확인
			if (PlayerController->WasInputKeyJustPressed(EKeys::G))
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Input G"));

				ENetworkType = EGrimNetworkType::B;
			}

			// 예: 'H' 키가 방금 놓였는지 확인
			if (PlayerController->WasInputKeyJustReleased(EKeys::H))
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Input H"));

				ENetworkType = EGrimNetworkType::C;
			}
		}
	}
}

void AGrimCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGrimCharacter, ENetworkType);
	DOREPLIFETIME_CONDITION(AGrimCharacter, MyVariable, COND_OwnerOnly);
}

void AGrimCharacter::OnRep_ProcessNetworkPacket()
{
	GrimHandler::ProcessNetworkPacket();
}

void AGrimCharacter::ServerRPC_Implementation()
{
}

void AGrimCharacter::MulticastRPC_Implementation()
{
}

bool AGrimCharacter::ServerRPC_Validate()
{
	return true;
}

void AGrimCharacter::ClientRPC_Implementation()
{
}

void AGrimCharacter::SetupDefault()
{
	JumpCurrentCount = 0;
	JumpMaxCount = 1;

	OldDirVector = FVector2d(0, 0);

	bIsTurn = false;
	IsAttacking = false;
	bPressAttack = false;

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	//CameraBoom->SetRelativeLocation(FVector(-20.f, 40.f, 70.f));

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

void AGrimCharacter::LoadMeshAnimation()
{
}

void AGrimCharacter::LoadEnhancedInput()
{
	//Load Mapping Context
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/05_Input/02_Grim/IM_Grim.IM_Grim'"));
	if (InputMappingContextRef.Object)
		DefaultMappingContext = InputMappingContextRef.Object;

	//Load Input Action
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionJumpRef(TEXT("/Script/EnhancedInput.InputAction'/Game/05_Input/02_Grim/InputAction/IA_Grim_Jump.IA_Grim_Jump'"));
	if (nullptr != InputActionJumpRef.Object)
		JumpAction = InputActionJumpRef.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/05_Input/02_Grim/InputAction/IA_Grim_Move.IA_Grim_Move'"));
	if (nullptr != InputActionMoveRef.Object)
		MoveAction = InputActionMoveRef.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionLookRef(TEXT("/Script/EnhancedInput.InputAction'/Game/05_Input/02_Grim/InputAction/IA_Grim_Look.IA_Grim_Look'"));
	if (nullptr != InputActionLookRef.Object)
		LookAction = InputActionLookRef.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionSkillEDRef(TEXT("/Script/EnhancedInput.InputAction'/Game/05_Input/02_Grim/InputAction/IA_Grim_LeftButton.IA_Grim_LeftButton'"));
	if (nullptr != InputActionSkillEDRef.Object)
		LeftButtonAction = InputActionSkillEDRef.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionSkillSSBRef(TEXT("/Script/EnhancedInput.InputAction'/Game/05_Input/02_Grim/InputAction/IA_Grim_RightButton.IA_Grim_RightButton'"));
	if (nullptr != InputActionSkillSSBRef.Object)
		RightButtonAction = InputActionSkillSSBRef.Object;
}

void AGrimCharacter::BindInputAction2Fuction(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGrimCharacter::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGrimCharacter::Look);
	EnhancedInputComponent->BindAction(LeftButtonAction, ETriggerEvent::Triggered, this, &AGrimCharacter::LeftButton);
	EnhancedInputComponent->BindAction(RightButtonAction, ETriggerEvent::Triggered, this, &AGrimCharacter::RightButton);
}

void AGrimCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	BindInputAction2Fuction(PlayerInputComponent);
}

void AGrimCharacter::Move(const FInputActionValue& Value)
{
	////S. 천천히 회전
	//FVector2D MovementVector = Value.Get<FVector2D>();

	//const FRotator Rotation = Controller->GetControlRotation();
	//const FRotator YawRotation(0, Rotation.Yaw, 0);

	//const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	//const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	//MoveForwardInput = MovementVector.Y;
	//MoveRightInput = MovementVector.X;


	//AddMovementInput(ForwardDirection, MovementVector.X);
	//AddMovementInput(RightDirection, MovementVector.Y);



	//bIsTurn = (FVector2D::DotProduct(OldDirVector, MovementVector.GetSafeNormal()) < 0) ? true : false;

	//OldDirVector = MovementVector.GetSafeNormal();
	////E. 

	FVector2D MovementVector = Value.Get<FVector2D>();

	FVector ForwardDirection = FVector(FollowCamera->GetForwardVector().X, FollowCamera->GetForwardVector().Y, 0).GetSafeNormal();
	FVector RightDirection = FVector(FollowCamera->GetRightVector().X, FollowCamera->GetRightVector().Y, 0).GetSafeNormal();

	MoveForwardInput = MovementVector.Y;
	MoveRightInput = MovementVector.X;

	FRotator ControlRot = GetControlRotation();

	FRotator YawRotation(0, NormalizeYaw(GetActorRotation().Yaw + CalculateYaw(ControlRot.Yaw, GetActorRotation().Yaw) * 0.2f), 0);

	// 카메라 방향으로 캐릭터 회전
	FQuat QuatRotation = FQuat(YawRotation);
	SetActorRotation(QuatRotation);

	AddMovementInput(ForwardDirection, MovementVector.X);
	AddMovementInput(RightDirection, MovementVector.Y);

	if (FVector2D::DotProduct(OldDirVector, MovementVector.GetSafeNormal()) < 0)
	{
		bIsTurn = true;
	}

	OldDirVector = MovementVector.GetSafeNormal();
}

void AGrimCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();



	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(-LookAxisVector.Y);
}

void AGrimCharacter::Jump()
{
	Super::Jump();
}

void AGrimCharacter::LeftButton(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Activated LeftButton Dagger");
}

void AGrimCharacter::RightButton(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Activated Right Dagger");
}

float AGrimCharacter::NormalizeYaw(float Yaw)
{
	while (Yaw >= 360.f) Yaw -= 360.0f;
	while (Yaw < 0) Yaw += 360.0f;
	return Yaw;
}

float AGrimCharacter::CalculateYaw(float DestYaw, float SourYaw)
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
