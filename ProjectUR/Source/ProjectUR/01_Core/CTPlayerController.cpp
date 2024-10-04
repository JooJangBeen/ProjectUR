// Fill out your copyright notice in the Description page of Project Settings.


#include "CTPlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "../11_Manager/Managers.h"


ACTPlayerController::ACTPlayerController() : Super::APlayerController()
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
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		Subsystem->AddMappingContext(DefaultMappingContext, 2e9);


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


