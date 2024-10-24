// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CTPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTUR_API ACTPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACTPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void PostNetInit() override;
	virtual void OnPossess(APawn* InPawn) override;



	//==================================================================================
	// Key Input
	//==================================================================================
protected:
	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UInputAction> WorldKeyAction;

	UFUNCTION()
	virtual void FucTestWorldKey(const FInputActionValue& Value);
};
