// Fill out your copyright notice in the Description page of Project Settings.


#include "PCNarbash.h"
#include "../NarbashStick.h"
#include "TimerManager.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PCNarbashAnimInstance.h"
#include "Kismet/KismetSystemLibrary.h"
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
	InitCameraSetting();
	InitProperties();
	InitializeCardData(ECharacterType::Narbash);

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
		EnhancedInputComponent->BindAction(SkillOneAction, ETriggerEvent::Started, this, &APCNarbash::ReadySkillOne);
		EnhancedInputComponent->BindAction(SkillOneAction, ETriggerEvent::Completed, this, &APCNarbash::StopSkillOne);
		EnhancedInputComponent->BindAction(SkillTwoAction, ETriggerEvent::Started, this, &APCNarbash::ReadySkillTwo);
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &APCNarbash::DashStart);
	}
}

void APCNarbash::InitProperties()
{
	SkillTwoDecSpeedLerpRate = 0.f;
	MoveForwardInput = 0.f;
	MoveRightInput = 0.f;
	CurCombo = 0;
	MaxCombo = 0;

	IsAttacking = false;
	bMoveFBLock = false;
	bMoveLRLock = false;
	bCamYawLock = false;
	bJumpingLock = false;

}

void APCNarbash::InitCameraSetting()
{
	

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

	PCAnimInstance->OnSkillOneEnd.AddLambda([this]()->void {
		bMoveFBLock = false;
		bMoveLRLock = false;
		bCamYawLock = false;
		bJumpingLock = false;
		bCamPitchLock = false;
		IsAttacking = false;

		StickActor->Destroy();

	});

	PCAnimInstance->OnSkillTwoStart.AddLambda([this]()->void {
		GetWorldTimerManager().ClearTimer(SkillTwoReadyTimer);
		SkillTwoDecSpeedLerpRate = 0.f;
		GetCharacterMovement()->MaxWalkSpeed = 300.f;
	});

	PCAnimInstance->OnSkillTwoEnd.AddLambda([this]()->void {
		GetCharacterMovement()->MaxWalkSpeed = 600.f;
		bJumpingLock = false;
		IsAttacking = false;
	});

	PCAnimInstance->OnThrowStick.AddLambda([this]()->void {
		ThrowStick();
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
	if(!bMoveFBLock)
		AddMovementInput(ForwardDirection, MovementVector.X);

	if(!bMoveLRLock)
		AddMovementInput(RightDirection, MovementVector.Y);

}

void APCNarbash::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// add yaw and pitch input to controller
	if(!bCamYawLock)
		AddControllerYawInput(LookAxisVector.X);

	if (!bCamPitchLock)
		AddControllerPitchInput(LookAxisVector.Y);

}

void APCNarbash::Jump()
{
	if (bJumpingLock) return;

	bPressedJump = true;
	JumpKeyHoldTime = 0.0f;

}

void APCNarbash::StopJumping()
{
	Super::StopJumping();

}

void APCNarbash::NormalAttack()
{
	if (!IsAttacking)
	{
		if (!bReadySkillOne)
		{
			PCAnimInstance->PlayNormalAttackMontage(CurCombo);
		}
		else
		{
			bMoveFBLock = true;
			bMoveLRLock = true;
			bCamYawLock = true;
			bJumpingLock = true;
			bCamPitchLock = true;
			bReadySkillOne = false;
			PCAnimInstance->PlaySkillOneMontage();
		}

		IsAttacking = true;
	}
	else
	{
		bPressAttack = true;
	}
	
}

void APCNarbash::DashStart()
{
	if (GetCharacterMovement()->IsFalling() || IsAttacking || bReadySkillOne) return;

	DashMoveValue = (DashDist * 100.f) / (MaxDashPlayTime / 0.01f);

	GetWorldTimerManager().SetTimer(DashTimer, this, &APCNarbash::Dash, 0.01f, true);
	PCAnimInstance->PlayDashMontage(1.f * (DashMoveValue * 0.08f));

	DashStartControllerRot = GetControlRotation();
	DashStartPlayerRot = GetActorRotation();
	ControllerRotLerpRate = 0.f;

	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 4.f;

	bMoveFBLock = true;
	bMoveLRLock = true;
	bCamYawLock = true;
	bJumpingLock = true;
	bCamPitchLock = true;

	IsAttacking = true;

}

void APCNarbash::Dash()
{
	CurDashPlayTime += 0.01f;
	ControllerRotLerpRate += 0.04f;

	if (ControllerRotLerpRate > 1.f) ControllerRotLerpRate = 1.f;

	if (CurDashPlayTime > MaxDashPlayTime)
	{
		PCAnimInstance->StopDashMontage();
		GetWorldTimerManager().ClearTimer(DashTimer);
		CurDashPlayTime = 0.f;

		bMoveFBLock = false;
		bMoveLRLock = false;
		bCamYawLock = false;
		bJumpingLock = false;
		bCamPitchLock = false;
		CameraBoom->bEnableCameraLag = false;

		IsAttacking = false;
	}
	else
	{
		SetActorLocation(GetActorLocation() + (GetActorForwardVector() * DashMoveValue));
		GetController()->SetControlRotation(FMath::Lerp(DashStartControllerRot, DashStartPlayerRot, ControllerRotLerpRate));
	}

	CameraBoom->CameraLagSpeed = FMath::InterpCircularIn(4.f, 50.f, (CurDashPlayTime / (MaxDashPlayTime)));

}

void APCNarbash::ReadySkillOne()
{
	if (!IsAttacking)
	{
		bReadySkillOne = true;
		PCAnimInstance->ReadySkillOneMontage();
	}

}

void APCNarbash::StopSkillOne()
{
	if (GetCharacterMovement()->IsFalling() || bReadySkillOne)
	{
		bReadySkillOne = false;
		PCAnimInstance->StopSkillOneMontage();
	}

}

void APCNarbash::ThrowStick()
{
	FVector SpawnPos, CamPose;
	FRotator SpawnRot;

	SpawnPos = GetMesh()->GetSocketLocation(FName("ThrowSocket"));
	GetController()->GetPlayerViewPoint(CamPose, SpawnRot);
	
	FVector LineTrace_Start = CamPose;
	FVector LineTrace_End = LineTrace_Start + SpawnRot.Vector() * 1500.f;
	FHitResult HitResult;
	TArray<AActor*> Ignore;
	Ignore.Add(this);
	bool bResult = false;
	bResult = UKismetSystemLibrary::LineTraceSingle(GetWorld(), LineTrace_Start, LineTrace_End, UEngineTypes::ConvertToTraceType(ECC_WorldStatic), true, Ignore, EDrawDebugTrace::None, HitResult, true);
	if (bResult)
	{
		SpawnRot = ((HitResult.Location - SpawnPos).GetSafeNormal()).Rotation();
	}
	else
	{
		SpawnRot = ((LineTrace_End - SpawnPos).GetSafeNormal()).Rotation();
	}
	
	StickActor = GetWorld()->SpawnActor<ANarbashStick>(StickActorClass, SpawnPos, SpawnRot);
	if (StickActor)
	{
		StickActor->AttachCableEnd(GetMesh(), FName("ThrowSocket"));
	}

}

void APCNarbash::ReadySkillTwo()
{
	if (IsAttacking) return;

	GetWorldTimerManager().SetTimer(SkillTwoReadyTimer, this, &APCNarbash::SkillTwoPrePose, 0.16f, true);
	bJumpingLock = true;
	IsAttacking = true;

	PCAnimInstance->ReadySkillTwoMontage();

}

void APCNarbash::SkillTwoPrePose()
{
	SkillTwoDecSpeedLerpRate += 0.1f;
	GetCharacterMovement()->MaxWalkSpeed = FMath::Lerp(600.f, 300.f, SkillTwoDecSpeedLerpRate);

}

void APCNarbash::StopSkillTwo()
{
	PCAnimInstance->StopSkillTwoMontage();
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
		SkillOneAction = IA_Skill1Asset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_Skill2Asset(TEXT("/Game/05_Input/00_PCNarbash/InputAction/IA_PCNarbash_Skill2.IA_PCNarbash_Skill2"));
	if (IA_Skill1Asset.Succeeded())
	{
		SkillTwoAction = IA_Skill2Asset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_DashAction(TEXT("/Game/05_Input/00_PCNarbash/InputAction/IA_PCNarbash_Dash.IA_PCNarbash_Dash"));
	if (IA_DashAction.Succeeded())
	{
		DashAction = IA_DashAction.Object;
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
