// Fill out your copyright notice in the Description page of Project Settings.


#include "CTPlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "../11_Manager/Managers.h"
#include "../ProjectUR.h"


ACTPlayerController::ACTPlayerController()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/05_Input/IM_WorldDefualt.IM_WorldDefualt'"));
	if (InputMappingContextRef.Object)
		DefaultMappingContext = InputMappingContextRef.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/05_Input/TestPlayerIA/IA_TestWorld.IA_TestWorld'"));
	if (nullptr != InputActionRef.Object)
		WorldKeyAction = InputActionRef.Object;


}

void ACTPlayerController::BeginPlay()
{
	PUR_LOG(LogNetwork, Log, TEXT("% s"), TEXT("Begin"));

	Super::BeginPlay();

	PUR_LOG(LogNetwork, Log, TEXT("% s"), TEXT("END"));

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		Subsystem->AddMappingContext(DefaultMappingContext, 2e9);

	GetMgr(UUIManager)->TurnAddRemove_UserWidgetGroup("InGameUIGroup");

}

void ACTPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();


	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInputComponent)
		EnhancedInputComponent->BindAction(WorldKeyAction, ETriggerEvent::Triggered, this, &ACTPlayerController::FucTestWorldKey);

}

void ACTPlayerController::FucTestWorldKey(const FInputActionValue& Value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "UITestInput");
	GetMgr(UUIManager)->TurnAddRemove_UserWidgetGroup("LevelUpCardUIGroup");
	
}


