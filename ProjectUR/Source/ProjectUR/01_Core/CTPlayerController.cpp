// Fill out your copyright notice in the Description page of Project Settings.


#include "CTPlayerController.h"

void ACTPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
}
