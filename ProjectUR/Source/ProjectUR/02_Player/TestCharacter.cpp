// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"



ATestCharacter::ATestCharacter()
{
	InteractionData.CurrentInteractableActor = nullptr;
	TargetInteractableActor = nullptr;

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;


	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

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


	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/02_Player/99_Resources/ParagonKallari/Characters/Heroes/Kallari/Meshes/Kallari.Kallari'"));

	if (CharacterMeshRef.Object)
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);


	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstClassRef(TEXT("/Game/02_Player/99_Resources/ParagonKallari/Characters/Heroes/Kallari/Kallari_AnimBlueprint.Kallari_AnimBlueprint_C"));

	if (AnimInstClassRef.Class)
		GetMesh()->SetAnimInstanceClass(AnimInstClassRef.Class);


	// Input
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/05_Input/IM_Default.IM_Default'"));
	if (InputMappingContextRef.Object)
		DefaultMappingContext = InputMappingContextRef.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/05_Input/TestPlayerIA/IA_TestMove.IA_TestMove'"));
	if (nullptr != InputActionMoveRef.Object)
		MoveAction = InputActionMoveRef.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionJumpRef(TEXT("/Script/EnhancedInput.InputAction'/Game/05_Input/TestPlayerIA/IA_TestJump.IA_TestJump'"));
	if (nullptr != InputActionJumpRef.Object)
		JumpAction = InputActionJumpRef.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionLookRef(TEXT("/Script/EnhancedInput.InputAction'/Game/05_Input/TestPlayerIA/IA_TestLook.IA_TestLook'"));
	if (nullptr != InputActionLookRef.Object)
		LookAction = InputActionLookRef.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionInterRef(TEXT("/Script/EnhancedInput.InputAction'/Game/05_Input/TestPlayerIA/IA_TestInterAct.IA_TestInterAct'"));
	if (nullptr != InputActionInterRef.Object)
		InterAction = InputActionInterRef.Object;




}

void ATestCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
		//Subsystem->RemoveMappingContext(DefaultMappingContext);
		//Subsystem->ClearAllMappings();
	}

	// Box Collision Component 초기화
	CollisionCapsule = FindComponentByClass<UCapsuleComponent>();
	//RootComponent = CollisionCapsule;

	// 콜리전 이벤트를 활성화
	CollisionCapsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionCapsule->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	CollisionCapsule->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	// Overlap 이벤트 바인딩
	CollisionCapsule->OnComponentBeginOverlap.AddDynamic(this, &ATestCharacter::TestCharacterOnOverlapBegin);

	InteractionData.CurrentInteractableActor = this;
}

void ATestCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//if (GetWorld()->TimeSince(InteractionData.LastInteractionCheckTime) > 0.1f)
	//	PerformRaycastCheck();
}

void ATestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//PlayerInputComponent->BindKey

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATestCharacter::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATestCharacter::Look);
	EnhancedInputComponent->BindAction(InterAction, ETriggerEvent::Triggered, this, &ATestCharacter::TestInterAct);
}

void ATestCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.X);
	AddMovementInput(RightDirection, MovementVector.Y);

	//
}

void ATestCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(-LookAxisVector.Y);
}



void ATestCharacter::TestCharacterOnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && OtherComp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Collision");
	}
}

void ATestCharacter::PerformRaycastCheck()
{
	InteractionData.CurrentInteractableActor = nullptr;
	TargetInteractableActor = nullptr;
	InteractionData.LastInteractionCheckTime = GetWorld()->GetRealTimeSeconds();

	FVector TraceStart{ GetPawnViewLocation() };
	FVector TraceEnd{ TraceStart + GetViewRotation().Vector() * 200.f };

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	FHitResult TraceHit;

	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 0.5f, 0 ,1.f);


	if (GetWorld()->LineTraceSingleByChannel(TraceHit, TraceStart, TraceEnd, ECC_Visibility, QueryParams))
	{
		if (TraceHit.GetActor()->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
		{
			if (TraceHit.GetActor() != InteractionData.CurrentInteractableActor)
			{
				InteractionData.CurrentInteractableActor = TraceHit.GetActor();
				TargetInteractableActor = InteractionData.CurrentInteractableActor;
				return;
			}
			else
			{
				return;
			}
		}
	}


	//====================================



}

void ATestCharacter::TestInterAct(const FInputActionValue& Value)
{
	if (InteractionData.CurrentInteractableActor == nullptr)
		return;

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Interacted2");
}

void ATestCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
	{
		if (OtherActor != InteractionData.CurrentInteractableActor)
		{
			InteractionData.CurrentInteractableActor = OtherActor;
			TargetInteractableActor = InteractionData.CurrentInteractableActor;
			return;
		}
		else
		{
			return;
		}
	}

}

void ATestCharacter::NotifyActorEndOverlap(AActor* OtherActor)
{
	InteractionData.CurrentInteractableActor = nullptr;
	TargetInteractableActor = nullptr;
}
