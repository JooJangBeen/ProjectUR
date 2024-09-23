// Fill out your copyright notice in the Description page of Project Settings.


#include "PCNarbash.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "../PCNarbashAnimInstance.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

APCNarbash::APCNarbash()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_MeshInfo(TEXT("/Game/02_Player/99_Resources/ParagonNarbash/Characters/Heroes/Narbash/Meshes/Narbash.Narbash"));
	if (SK_MeshInfo.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_MeshInfo.Object);
	}

	static ConstructorHelpers::FClassFinder<UPCNarbashAnimInstance> BP_AnimInst(TEXT("/Game/01_Blueprint/02_PCNarbash/ABP_PCNarbash.ABP_PCNarbash_C"));
	if (BP_AnimInst.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(BP_AnimInst.Class);
	}

	InitMappingContextSetting();

	MoveForwardInput = 0.f;
	MoveRightInput = 0.f;
	CurCombo = 0;
	MaxCombo = 0;

	IsAttacking = false;
}

void APCNarbash::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	PCAnimInstance = Cast<UPCNarbashAnimInstance>(GetMesh()->GetAnimInstance());
	SetupNotifys();

}

void APCNarbash::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APCNarbash::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APCNarbash::Look);

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APCNarbash::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APCNarbash::StopJumping);
		
		EnhancedInputComponent->BindAction(NormalAttackAction, ETriggerEvent::Started, this, &APCNarbash::NormalAttack);
		EnhancedInputComponent->BindAction(Skill1Action, ETriggerEvent::Started, this, &APCNarbash::Skill1Attack);
	}
}

void APCNarbash::SetupNotifys()
{
	if (!IsValid(PCAnimInstance))
	{
		UE_LOG(LogTemp, Error, TEXT("Not Exist AnimInstance"));
	}

	PCAnimInstance->OnAttackEnd.AddLambda([this]()->void {
		IsAttacking = false;
		bPressAttack = false;
		CurCombo = 0;
	});

	PCAnimInstance->OnNextComboCheck.AddLambda([this]()->void {
		if (bPressAttack)
		{
			CurCombo = (CurCombo + 1) % MaxCombo;
			bPressAttack = false;
			PCAnimInstance->PlayNormalAttackMontage(CurCombo);
		}
	});

	PCAnimInstance->OnSkill1End.AddLambda([this]()->void {
		IsAttacking = false;
	});

}

void APCNarbash::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// find out which way is forward
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	// get right vector 
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	MoveForwardInput = MovementVector.X;
	MoveRightInput = MovementVector.Y;

	// add movement 
	AddMovementInput(ForwardDirection, MovementVector.X);
	AddMovementInput(RightDirection, MovementVector.Y);

}

void APCNarbash::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// add yaw and pitch input to controller
	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);

}

void APCNarbash::Jump()
{
	Super::Jump();

}

void APCNarbash::StopJumping()
{
	Super::StopJumping();

}

void APCNarbash::NormalAttack()
{
	if (!IsAttacking)
	{
		PCAnimInstance->PlayNormalAttackMontage(CurCombo);
		IsAttacking = true;
	}
	else
	{
		bPressAttack = true;
	}
	
}

void APCNarbash::Skill1Attack()
{
	if (!IsAttacking)
	{
		PCAnimInstance->PlaySkill1Montage();
		IsAttacking = true;
	}

}

void APCNarbash::InitMappingContextSetting()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IM_ContextAsset(TEXT("/Game/05_Input/00_PCNarbash/MappingContext/IM_PCNarbashDefault.IM_PCNarbashDefault"));
	if(IM_ContextAsset.Succeeded())
	{
		DefaultMappingContext = IM_ContextAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_MoveAsset(TEXT("/Game/05_Input/00_PCNarbash/InputAction/IA_PCNarbash_Move.IA_PCNarbash_Move"));
	if (IA_MoveAsset.Succeeded())
	{
		MoveAction = IA_MoveAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_LookAsset(TEXT("/Game/05_Input/00_PCNarbash/InputAction/IA_PCNarbash_Look.IA_PCNarbash_Look"));
	if (IA_LookAsset.Succeeded())
	{
		LookAction = IA_LookAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_JumpAsset(TEXT("/Game/05_Input/00_PCNarbash/InputAction/IA_PCNarbash_Jump.IA_PCNarbash_Jump"));
	if (IA_JumpAsset.Succeeded())
	{
		JumpAction = IA_JumpAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_NormalAttackAsset(TEXT("/Game/05_Input/00_PCNarbash/InputAction/IA_PCNarbash_NormalAttack.IA_PCNarbash_NormalAttack"));
	if (IA_NormalAttackAsset.Succeeded())
	{
		NormalAttackAction = IA_NormalAttackAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_Skill1Asset(TEXT("/Game/05_Input/00_PCNarbash/InputAction/IA_PCNarbash_Skill1.IA_PCNarbash_Skill1"));
	if (IA_Skill1Asset.Succeeded())
	{
		Skill1Action = IA_Skill1Asset.Object;
	}

}

float APCNarbash::GetMoveForwardInput()
{
	return MoveForwardInput;

}

float APCNarbash::GetMoveRightInput()
{
	return MoveRightInput;

}
