// Fill out your copyright notice in the Description page of Project Settings.


#include "KallariCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KallariAnimInstance.h"
#include "Math.h"
#include "../04_Actor/02_KallariDagger/KallariDagger.h"
#include "../11_Manager/Managers.h"
#include "../07_UI/02_IngameUI/UW_Crosshair.h"


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

	Setup_MoveRestrictAnimNotify();
	Setup_SkillAnimNotify();
}

void AKallariCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CheckDagger(DeltaSeconds);
	RestrictMove(DeltaSeconds);


}

void AKallariCharacter::SetupDefault()
{
	JumpCurrentCount = 0;
	JumpMaxCount = 2;
	TurnTimer = 0;
	GroundComboAtkCount = 0;
	iGroundComboChecker = 0;

	OldDirVector = FVector2d(0, 0);

	bDashMove = false;
	bNeedToCheckDagger = true;
	bTargettedDagger = false;
	bIsTurn = false;
	bRestrictMove = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;



	FollowCamera->SetRelativeLocation(FVector(70.f, 40.f, 75.f));

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = KallariDefault_JumpZVelocity;
	GetCharacterMovement()->AirControl = KallariDefault_AirControl;
	GetCharacterMovement()->MaxWalkSpeed = KallariDefault_MaxWalkSpped;
	GetCharacterMovement()->MinAnalogWalkSpeed = KallariDefault_MinAnalogWalkSpeed;
	GetCharacterMovement()->BrakingDecelerationWalking = KallariDefault_BrakingDecelerationWalking;


	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -100.f), FRotator(0, -90.f, 0.f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName((TEXT("CharacterMesh")));

	static ConstructorHelpers::FClassFinder<AKallariDagger> ProjectileBPClass(TEXT("/Game/02_Player/01_Kallari/KallariDagger.KallariDagger_C"));
	check(ProjectileBPClass.Class);

	EclipseDagger = ProjectileBPClass.Class;
	
}


void AKallariCharacter::LoadMeshAnimation()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/02_Player/99_Resources/ParagonKallari/Characters/Heroes/Kallari/Skins/Tough/Meshes/Kallari_Tough.Kallari_Tough'"));
	if (CharacterMeshRef.Object)
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstClassRef(TEXT("/Game/02_Player/01_Kallari/ABP_Kallari.ABP_Kallari_C"));
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
	InputActionArray.SetNum(int(EKallariInputAction::END));

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionJumpRef(TEXT("/Script/EnhancedInput.InputAction'/Game/05_Input/01_Kallari/InputAction/IA_KallariJump.IA_KallariJump'"));
	if (nullptr != InputActionJumpRef.Object)
		InputActionArray[int(EKallariInputAction::JumpAction)] = InputActionJumpRef.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/05_Input/01_Kallari/InputAction/IA_KallariMove.IA_KallariMove'"));
	if (nullptr != InputActionMoveRef.Object)
		InputActionArray[int(EKallariInputAction::MoveAction)] = InputActionMoveRef.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionLookRef(TEXT("/Script/EnhancedInput.InputAction'/Game/05_Input/01_Kallari/InputAction/IA_KallariLook.IA_KallariLook'"));
	if (nullptr != InputActionLookRef.Object)
		InputActionArray[int(EKallariInputAction::LookAction)] = InputActionLookRef.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionSkillEDRef(TEXT("/Script/EnhancedInput.InputAction'/Game/05_Input/01_Kallari/InputAction/IA_KallariSkillED.IA_KallariSkillED'"));
	if (nullptr != InputActionSkillEDRef.Object)
		InputActionArray[int(EKallariInputAction::SkillEDAction)] = InputActionSkillEDRef.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionSkillSSBRef(TEXT("/Script/EnhancedInput.InputAction'/Game/05_Input/01_Kallari/InputAction/IA_KallariSkillSSB.IA_KallariSkillSSB'"));
	if (nullptr != InputActionSkillSSBRef.Object)
		InputActionArray[int(EKallariInputAction::SkillSSBAction)] = InputActionSkillSSBRef.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionSkillAHARef(TEXT("/Script/EnhancedInput.InputAction'/Game/05_Input/01_Kallari/InputAction/IA_KallariSkillAHA.IA_KallariSkillAHA'"));
	if (nullptr != InputActionSkillAHARef.Object)
		InputActionArray[int(EKallariInputAction::SkillAHAAction)] = InputActionSkillAHARef.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionComboAtkRef(TEXT("/Script/EnhancedInput.InputAction'/Game/05_Input/01_Kallari/InputAction/IA_KallariBasicAtk.IA_KallariBasicAtk'"));
	if (nullptr != InputActionComboAtkRef.Object)
		InputActionArray[int(EKallariInputAction::GroundComboAtk)] = InputActionComboAtkRef.Object;

}

void AKallariCharacter::BindInputAction2Fuction(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(InputActionArray[int(EKallariInputAction::JumpAction)], ETriggerEvent::Triggered, this, &AKallariCharacter::Jump);
	EnhancedInputComponent->BindAction(InputActionArray[int(EKallariInputAction::JumpAction)], ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInputComponent->BindAction(InputActionArray[int(EKallariInputAction::MoveAction)], ETriggerEvent::Triggered, this, &AKallariCharacter::Move);
	EnhancedInputComponent->BindAction(InputActionArray[int(EKallariInputAction::LookAction)], ETriggerEvent::Triggered, this, &AKallariCharacter::Look);
	EnhancedInputComponent->BindAction(InputActionArray[int(EKallariInputAction::SkillEDAction)], ETriggerEvent::Triggered, this, &AKallariCharacter::Skill_ED);
	EnhancedInputComponent->BindAction(InputActionArray[int(EKallariInputAction::SkillSSBAction)], ETriggerEvent::Triggered, this, &AKallariCharacter::Skill_SSB);
	EnhancedInputComponent->BindAction(InputActionArray[int(EKallariInputAction::SkillAHAAction)], ETriggerEvent::Triggered, this, &AKallariCharacter::Skill_AHA);
	EnhancedInputComponent->BindAction(InputActionArray[int(EKallariInputAction::GroundComboAtk)], ETriggerEvent::Triggered, this, &AKallariCharacter::GroundComboAtk);
}

void AKallariCharacter::CheckDagger(float DeltaSeconds)
{
	if (bNeedToCheckDagger)
	{

		FVector CamPos;
		FRotator SpawnRot;

		GetController()->GetPlayerViewPoint(CamPos, SpawnRot);

		FVector LineTrace_Start = CamPos;
		FVector LineTrace_End = LineTrace_Start + SpawnRot.Vector() * 2500.f;
		FHitResult HitResult;
		TArray<AActor*> Ignore;
		Ignore.Add(this);
		bool bResult = false;

		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this); // 무시할 액터 추가
		CollisionParams.bTraceComplex = true; // 복잡한 트레이스 여부
		CollisionParams.bReturnPhysicalMaterial = false; // 물리 재질 반환 여부

		FCollisionShape SphereShape = FCollisionShape::MakeSphere(1.f);
		bResult = GetWorld()->SweepSingleByChannel(HitResult, LineTrace_Start, LineTrace_End, FQuat::Identity, ECC_Camera, SphereShape, CollisionParams);


		if (bResult && HitResult.GetActor()->IsA(AKallariDagger::StaticClass()))
		{
			AKallariDagger* Dagger = Cast<AKallariDagger>(HitResult.GetActor());
			check(Dagger != nullptr);

			if (Dagger->GetIsOnGround())
			{
				if (!bTargettedDagger)
				{
					UUW_Crosshair* pCrosshair = Cast<UUW_Crosshair>(GetMgr(UUIManager)->GetUserWidget(FName("Crosshair")));
					check(pCrosshair != nullptr);
					pCrosshair->SetMainColor(FLinearColor(0, 0.2f, 1.f));
					bTargettedDagger = true;

				}
				TargettedDagger = Dagger;
			}
		}
		else if (bTargettedDagger)
		{
			bTargettedDagger = false;
			UUW_Crosshair* pCrosshair = Cast<UUW_Crosshair>(GetMgr(UUIManager)->GetUserWidget(FName("Crosshair")));
			check(pCrosshair != nullptr);

			pCrosshair->ResetMainColor();
			TargettedDagger = nullptr;
		}

		if (TargettedDagger && !TargettedDagger->IsValidLowLevel())
		{
			TargettedDagger = nullptr;
			bTargettedDagger = false;
		}
	}

}

void AKallariCharacter::RestrictMove(float DeltaSeconds)
{
	/*
	if (bIsTurn)
	{
		TurnTimer += DeltaSeconds;
		if (TurnTimer > 0.2f)
		{
			bIsTurn = false;
			TurnTimer = 0;
		}
	}
	*/
	if (bRestrictMove)
		SetActorLocation(GetActorLocation() + (RestrictMoveDir * RestrictMoveSpeed * DeltaSeconds));
	else if (bDashMove)
	{
		FRotator ControlRot = GetControlRotation();
		FRotator YawRotation(0, NormalizeYaw(GetActorRotation().Yaw + CalculateYaw(ControlRot.Yaw, GetActorRotation().Yaw) * 0.2f), 0);
		FQuat QuatRotation = FQuat(YawRotation);
		SetActorRotation(QuatRotation);

		FVector ForwardDirection = FVector(FollowCamera->GetForwardVector().X, FollowCamera->GetForwardVector().Y, 0).GetSafeNormal();
		AddMovementInput(ForwardDirection, 1);
	}

}

void AKallariCharacter::Setup_SkillAnimNotify()
{
	if (!pAnimInstance)
	{
		pAnimInstance = Cast<UKallariAnimInstance>(GetMesh()->GetAnimInstance());
		check(pAnimInstance);
	}

	//For ComboAtk
	pAnimInstance->GetAnimNotifyDeligate(EKallariAnimNotify::CheckNextCombo)->AddLambda([this]()->void
		{
			iGroundComboChecker = 0b00000011;
		});
	pAnimInstance->GetAnimNotifyDeligate(EKallariAnimNotify::PlayNextCombo)->AddLambda([this]()->void
		{
			if (iGroundComboChecker == 1)
			{
				FName ComboSection = FName(FString::Printf(TEXT("ATK_%d"), GroundComboAtkCount));
				if (pAnimInstance->Montage_GetCurrentSection(pAnimInstance->GetAnimMontage(EKallariMTG::GroundComboAtk)) != ComboSection)
					pAnimInstance->PlayAnimMontage(EKallariMTG::GroundComboAtk, ComboSection);
			}
		});
	pAnimInstance->GetAnimNotifyDeligate(EKallariAnimNotify::StopComboAtk)->AddLambda([this]()->void
		{
			GroundComboAtkCount = 0;
			iGroundComboChecker = 0;
		});


	//For EclipseDagger
	pAnimInstance->GetAnimNotifyDeligate(EKallariAnimNotify::DeAimDagger)->AddLambda([this]()->void 
		{

		if (pAnimInstance->Montage_GetCurrentSection(pAnimInstance->GetAnimMontage(EKallariMTG::EclipseDagger)) != FName("Throw_3"))
			pAnimInstance->StopAnimMontage(EKallariMTG::EclipseDagger);
		});
	pAnimInstance->GetAnimNotifyDeligate(EKallariAnimNotify::ThrowDagger)->AddLambda([this]()->void
		{
			//sword_handle_r
			FVector SpawnLocation, CamPos;
			FRotator SpawnRotation;

			SpawnLocation = GetMesh()->GetSocketLocation(FName("sword_handle_r"));
			GetController()->GetPlayerViewPoint(CamPos, SpawnRotation);

			SpawnRotation = (((CamPos + SpawnRotation.Vector() * 1500.f) - SpawnLocation).GetSafeNormal()).Rotation();

			TObjectPtr<AKallariDagger> ECDagger = GetWorld()->SpawnActor<AKallariDagger>(EclipseDagger, SpawnLocation, SpawnRotation);

			if (ECDagger)
			{
				// 투사체 발사
				ECDagger->FireInDirection(SpawnRotation.Vector());
			}

		});


	//For ShadowStep
	pAnimInstance->GetAnimNotifyDeligate(EKallariAnimNotify::ShadowStepStart)->AddLambda([this]()->void
		{
			bDashMove = true;
		});
	pAnimInstance->GetAnimNotifyDeligate(EKallariAnimNotify::ShadowStepEnd)->AddLambda([this]()->void
		{
			bDashMove = false;
		});

	//For Blink
	pAnimInstance->GetAnimNotifyDeligate(EKallariAnimNotify::BlinkCameraLagSet)->AddLambda([this]()->void
		{


			FRotator ControlRot = GetControlRotation();
			FRotator YawRotation(0, ControlRot.Yaw, 0);
			FQuat QuatRotation = FQuat(YawRotation);
			SetActorRotation(QuatRotation);

			BlickCameraTimer = 0;
			StartArmLength = PLAYERDEFAULTCAMLENTH;
			TargetArmLength = 500.f;
			InterpSpeed = 0.48f;
			GetWorld()->GetTimerManager().SetTimer(CameraLagTimerHandle, this, &AKallariCharacter::UpdateCameraZoom, GetWorld()->GetDeltaSeconds(), true);


		});
	pAnimInstance->GetAnimNotifyDeligate(EKallariAnimNotify::BlinkMoveFwd)->AddLambda([this]()->void
		{
			bRestrictMove = true;

			BlinkTargetPos = TargettedDagger->GetHittedGroundPos() + (TargettedDagger->GetActorLocation() - TargettedDagger->GetHittedGroundPos()).GetSafeNormal() * 100.f;
			RestrictMoveDir = (BlinkTargetPos - GetActorLocation()).GetSafeNormal();
			RestrictMoveSpeed = (BlinkTargetPos - GetActorLocation()).Size() * 0.7f / 0.24f;
			BlickCameraTimer = 0;

			CameraBoom->bEnableCameraLag = true;          // 카메라 위치 지연 활성화
			CameraBoom->CameraLagSpeed = 7.0f;            // 카메라가 따라오는 속도 (값이 낮을수록 더 느리게)
			CameraBoom->CameraLagMaxDistance = 3000.0f;    // 최대 지연 거리

			FVector CameraLocation = FollowCamera->GetComponentLocation();
			FVector TargetLocation = CameraBoom->GetComponentLocation();
			float ActualDistance = FVector::Dist(CameraLocation, TargetLocation);
			StartArmLength = ActualDistance;
			TargetArmLength = PLAYERDEFAULTCAMLENTH;
			InterpSpeed = 0.6f;
			GetWorld()->GetTimerManager().SetTimer(CameraLagTimerHandle, this, &AKallariCharacter::UpdateCameraZoom, GetWorld()->GetDeltaSeconds(), true);

		});
	pAnimInstance->GetAnimNotifyDeligate(EKallariAnimNotify::BlinkTeleport)->AddLambda([this]()->void
		{
			bRestrictMove = false;














			SetActorLocation(BlinkTargetPos);

		});
	pAnimInstance->GetAnimNotifyDeligate(EKallariAnimNotify::BlinkEnd)->AddLambda([this]()->void
		{
			bNeedToCheckDagger = true;
			bRestrictMove = false;
			CameraBoom->bEnableCameraLag = false;
			CameraBoom->TargetArmLength = PLAYERDEFAULTCAMLENTH;
		});
	

	//For Annihilation
	pAnimInstance->GetAnimNotifyDeligate(EKallariAnimNotify::AnhilSetup)->AddLambda([this]()->void
		{
			RestrictMoveDir = FollowCamera->GetForwardVector();
			RestrictMoveDir.Z = 0;
			RestrictMoveDir = RestrictMoveDir.GetSafeNormal();
			BlinkTargetPos = GetActorLocation() + (RestrictMoveDir * 1500.0f);
			RestrictMoveSpeed = (BlinkTargetPos - GetActorLocation()).Size() * 0.3f / 0.5f;
			BlickCameraTimer = 0;

			FRotator ControlRot = GetControlRotation();
			FRotator YawRotation(0, ControlRot.Yaw, 0);
			FQuat QuatRotation = FQuat(YawRotation);
			SetActorRotation(QuatRotation);



			StartArmLength = PLAYERDEFAULTCAMLENTH;
			TargetArmLength = 500.f;
			InterpSpeed = 0.40f;
			GetWorld()->GetTimerManager().SetTimer(CameraLagTimerHandle, this, &AKallariCharacter::UpdateCameraZoom, 0.01f, true);


		});
	pAnimInstance->GetAnimNotifyDeligate(EKallariAnimNotify::AnhilNextSlot)->AddLambda([this]()->void
		{
			//타겟 위치가 공중이면
			if (true)
				pAnimInstance->PlayAnimMontage(EKallariMTG::Annihilation, FName("Ulti_1"), 1.f);
			else
				pAnimInstance->PlayAnimMontage(EKallariMTG::Annihilation, FName("Ulti_2"), 1.f);


		});
	pAnimInstance->GetAnimNotifyDeligate(EKallariAnimNotify::AnhilTeleport)->AddLambda([this]()->void
		{
			CameraBoom->bEnableCameraLag = true;          // 카메라 위치 지연 활성화
			CameraBoom->CameraLagSpeed = 5.0f;            // 카메라가 따라오는 속도 (값이 낮을수록 더 느리게)
			CameraBoom->CameraLagMaxDistance = 100000.0f;    // 최대 지연 거리



			bRestrictMove = true;
			SetActorLocation(BlinkTargetPos);


		});
	pAnimInstance->GetAnimNotifyDeligate(EKallariAnimNotify::AnhilCamLagEnd)->AddLambda([this]()->void
		{
			bRestrictMove = false;

			FVector CameraLocation = FollowCamera->GetComponentLocation();
			FVector TargetLocation = CameraBoom->GetComponentLocation();
			float ActualDistance = FVector::Dist(CameraLocation, TargetLocation);
			StartArmLength = ActualDistance;
			TargetArmLength = PLAYERDEFAULTCAMLENTH;
			InterpSpeed = 0.8f;
			GetWorld()->GetTimerManager().SetTimer(CameraLagTimerHandle, this, &AKallariCharacter::UpdateCameraZoom, 0.01f, true);
			
		});
	pAnimInstance->GetAnimNotifyDeligate(EKallariAnimNotify::AnhilEnd)->AddLambda([this]()->void
		{

			CameraBoom->bEnableCameraLag = false;

		});
}

void AKallariCharacter::Setup_MoveRestrictAnimNotify()
{
	if (!pAnimInstance)
	{
		pAnimInstance = Cast<UKallariAnimInstance>(GetMesh()->GetAnimInstance());
		check(pAnimInstance);
	}

	pAnimInstance->GetAnimNotifyDeligate(EKallariAnimNotify::BlockMoveFB)->AddLambda([this]()->void
		{	bMoveFBLock = true;	});
	pAnimInstance->GetAnimNotifyDeligate(EKallariAnimNotify::BlockMoveLR)->AddLambda([this]()->void
		{	bMoveLRLock = true;	});
	pAnimInstance->GetAnimNotifyDeligate(EKallariAnimNotify::BlockMoveB)->AddLambda([this]()->void
		{	bMoveBLock = true;	});
	pAnimInstance->GetAnimNotifyDeligate(EKallariAnimNotify::BlockJump)->AddLambda([this]()->void
		{	bJumpingLock = true;	});
	pAnimInstance->GetAnimNotifyDeligate(EKallariAnimNotify::BlockCameraYaw)->AddLambda([this]()->void
		{	bCamYawLock = true;	});
	pAnimInstance->GetAnimNotifyDeligate(EKallariAnimNotify::BlockCameraPitch)->AddLambda([this]()->void
		{	bCamPitchLock = true;	});	
	pAnimInstance->GetAnimNotifyDeligate(EKallariAnimNotify::UnBlockMoveFB)->AddLambda([this]()->void
		{	bMoveFBLock = false;	});
	pAnimInstance->GetAnimNotifyDeligate(EKallariAnimNotify::UnBlockMoveLR)->AddLambda([this]()->void
		{	bMoveLRLock = false;	});
	pAnimInstance->GetAnimNotifyDeligate(EKallariAnimNotify::UnBlockMoveB)->AddLambda([this]()->void
		{	bMoveBLock = false;	});
	pAnimInstance->GetAnimNotifyDeligate(EKallariAnimNotify::UnBlockJump)->AddLambda([this]()->void
		{	bJumpingLock = false;	});
	pAnimInstance->GetAnimNotifyDeligate(EKallariAnimNotify::UnBlockCameraYaw)->AddLambda([this]()->void
		{	bCamYawLock = false;	});
	pAnimInstance->GetAnimNotifyDeligate(EKallariAnimNotify::UnBlockCameraPitch)->AddLambda([this]()->void
		{	bCamPitchLock = false;	});
	pAnimInstance->GetAnimNotifyDeligate(EKallariAnimNotify::UnBlockAll)->AddLambda([this]()->void
		{	
			bCamYawLock = false;
			bCamPitchLock = false;
			bMoveFBLock = false;
			bMoveLRLock = false;
			bJumpingLock = false;
			bMoveBLock = false;

			GetCharacterMovement()->JumpZVelocity = KallariDefault_JumpZVelocity;
			GetCharacterMovement()->AirControl = KallariDefault_AirControl;
			GetCharacterMovement()->MaxWalkSpeed = KallariDefault_MaxWalkSpped;
			GetCharacterMovement()->MinAnalogWalkSpeed = KallariDefault_MinAnalogWalkSpeed;
			GetCharacterMovement()->BrakingDecelerationWalking = KallariDefault_BrakingDecelerationWalking;
		});
	pAnimInstance->GetAnimNotifyDeligate(EKallariAnimNotify::BlocakAll)->AddLambda([this]()->void
		{
			bCamYawLock = true;
			bCamPitchLock = true;
			bMoveFBLock = true;
			bMoveLRLock = true;
			bJumpingLock = true;
		});
	pAnimInstance->GetAnimNotifyDeligate(EKallariAnimNotify::BlockAllMove)->AddLambda([this]()->void
		{
			bMoveFBLock = true;
			bMoveLRLock = true;
		});
	pAnimInstance->GetAnimNotifyDeligate(EKallariAnimNotify::BlockAllCameraCtrl)->AddLambda([this]()->void
		{
			bCamYawLock = true;
			bCamPitchLock = true;
		});

	pAnimInstance->GetAnimNotifyDeligate(EKallariAnimNotify::BlockAllMoveJump)->AddLambda([this]()->void
		{
			bMoveFBLock = true;
			bMoveLRLock = true;
			bJumpingLock = true;
		});
	

}

void AKallariCharacter::Move(const FInputActionValue& Value)
{
	if (bRestrictMove) return;

	FVector2D MovementVector = Value.Get<FVector2D>();

	if (bMoveBLock && MovementVector.Y < 0)
		MovementVector.Y = 0;

	FVector ForwardDirection = FVector(FollowCamera->GetForwardVector().X, FollowCamera->GetForwardVector().Y, 0).GetSafeNormal();
	FVector RightDirection = FVector(FollowCamera->GetRightVector().X, FollowCamera->GetRightVector().Y, 0).GetSafeNormal();

	MoveForwardInput = MovementVector.X;
	MoveRightInput = MovementVector.Y;

	FRotator ControlRot = GetControlRotation();

	FRotator YawRotation(0, NormalizeYaw(GetActorRotation().Yaw + CalculateYaw(ControlRot.Yaw , GetActorRotation().Yaw) * 0.2f), 0);
	
	// 카메라 방향으로 캐릭터 회전
	FQuat QuatRotation = FQuat(YawRotation);
	SetActorRotation(QuatRotation);


	if (!bMoveFBLock)
		AddMovementInput(ForwardDirection, MovementVector.Y);
	if (!bMoveLRLock)
		AddMovementInput(RightDirection, MovementVector.X);

	if (FVector2D::DotProduct(OldDirVector, MovementVector.GetSafeNormal()) < 0)
	{
		bIsTurn = true;
		TurnTimer = 0;
	}

	OldDirVector = MovementVector.GetSafeNormal();
}

void AKallariCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (!bCamYawLock)
		AddControllerYawInput(LookAxisVector.X);
	if (!bCamPitchLock)
		AddControllerPitchInput(-LookAxisVector.Y);
}
void AKallariCharacter::Jump()
{
	if (bJumpingLock) return;
	Super::Jump();

}

void AKallariCharacter::GroundComboAtk(const FInputActionValue& Value)
{
	FVector2D MouseInput = Value.Get<FVector2D>();
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Eclipse Dagger Input : %f, %f"), MouseInput.X, MouseInput.Y));
	
	if (!pAnimInstance->Montage_IsPlaying(pAnimInstance->GetAnimMontage(EKallariMTG::GroundComboAtk)))
	{
		GroundComboAtkCount = 0;
		iGroundComboChecker = 0;
	}



	if (MouseInput.Y || (iGroundComboChecker == 0b00000001)) return;
	

	if (!iGroundComboChecker)
	{
		iGroundComboChecker = 0b00000001;
		pAnimInstance->PlayAnimMontage(EKallariMTG::GroundComboAtk);
		return;
	}


	if (iGroundComboChecker & (1 << 1))
	{
		GroundComboAtkCount++;
		iGroundComboChecker = 0b00000001;

		if (GroundComboAtkCount > 2)
			GroundComboAtkCount = 0;
	}

	//FName ComboSection = FName(FString::Printf(TEXT("ATK_%d"), GroundComboAtkCount));
	//pAnimInstance->PlayAnimMontage(EKallariMTG::GroundComboAtk, ComboSection);

}
void AKallariCharacter::Skill_ED(const FInputActionValue& Value)
{
	FVector2D MouseInput = Value.Get<FVector2D>();


	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Eclipse Dagger Input : %f, %f"), MouseInput.X, MouseInput.Y));

	if (!MouseInput.X && MouseInput.Y)
	{
		pAnimInstance->BroadCastAnimNotify(EKallariAnimNotify::AimDagger);
		pAnimInstance->PlayAnimMontage(EKallariMTG::EclipseDagger);
	}
	else if (MouseInput.X && MouseInput.Y)
	{
		if (pAnimInstance->Montage_IsPlaying(pAnimInstance->GetAnimMontage(EKallariMTG::EclipseDagger)) &&
			pAnimInstance->Montage_GetCurrentSection(pAnimInstance->GetAnimMontage(EKallariMTG::EclipseDagger)) == FName("Throw_2"))
		{
			FQuat QuatRotation = FQuat(FRotator(0, GetControlRotation().Yaw, 0));
			SetActorRotation(QuatRotation);
			pAnimInstance->PlayAnimMontage(EKallariMTG::EclipseDagger, FName("Throw_3"));
		}
	}
	else if (!MouseInput.Y)
	{

		pAnimInstance->BroadCastAnimNotify(EKallariAnimNotify::DeAimDagger);
	}


}

void AKallariCharacter::Skill_SSB(const FInputActionValue& Value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Activated Skill Shadow step/Blink");


	float KeyInput = Value.Get<float>();

	if (KeyInput > 0)
	{
		if (bTargettedDagger && TargettedDagger && TargettedDagger->IsValidLowLevel())
		{
			if (!pAnimInstance->Montage_IsPlaying(pAnimInstance->GetAnimMontage(EKallariMTG::Blink)) &&
				!pAnimInstance->Montage_IsPlaying(pAnimInstance->GetAnimMontage(EKallariMTG::ShadowStep)))
			{
				pAnimInstance->PlayAnimMontage(EKallariMTG::Blink, 1.5f);
				TargettedDagger->SetLifeSpan(10.0);
				bNeedToCheckDagger = false;
			}
		}
		else
		{

			if (!GetCharacterMovement()->IsFalling())
			{
				pAnimInstance->PlayAnimMontage(EKallariMTG::ShadowStep);
			}
		}
	}
	else
	{
		if (pAnimInstance->Montage_IsPlaying(pAnimInstance->GetAnimMontage(EKallariMTG::ShadowStep))
			&& (pAnimInstance->Montage_GetCurrentSection() != FName("Sprint_2")))
			pAnimInstance->PlayAnimMontage(EKallariMTG::ShadowStep, FName("Sprint_2"));
	}


}

void AKallariCharacter::Skill_AHA(const FInputActionValue& Value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Activated Skill Annihilation");


	pAnimInstance->PlayAnimMontage(EKallariMTG::Annihilation, 0.3f);

}

void AKallariCharacter::UpdateCameraZoom()
{
	BlickCameraTimer += GetWorld()->GetDeltaSeconds();

	float CurrentArmLength = FMath::Lerp(StartArmLength, TargetArmLength, BlickCameraTimer / InterpSpeed);
	CameraBoom->TargetArmLength = CurrentArmLength;


	if (StartArmLength > TargetArmLength)
	{
		if (CurrentArmLength < TargetArmLength)
		{
			CameraBoom->TargetArmLength = TargetArmLength;
			// 타이머를 멈추고 완료
			GetWorld()->GetTimerManager().ClearTimer(CameraLagTimerHandle);
		}
	}
	else
	{
		if (CurrentArmLength > TargetArmLength)
		{
			CameraBoom->TargetArmLength = TargetArmLength;
			// 타이머를 멈추고 완료
			GetWorld()->GetTimerManager().ClearTimer(CameraLagTimerHandle);
		}
	}


}

float AKallariCharacter::NormalizeYaw(float Yaw)
{
	while (Yaw >= 360.f) Yaw -= 360.0f;
	while (Yaw < 0) Yaw += 360.0f;
	return Yaw;
}

float AKallariCharacter::CalculateYaw(float DestYaw, float SourYaw)
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

