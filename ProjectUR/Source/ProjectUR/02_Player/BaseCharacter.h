// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "../04_Actor/01_InteractableActor/InteractionInterface.h"
#include "BaseCharacter.generated.h"

USTRUCT()
struct FInteractionData
{
	GENERATED_USTRUCT_BODY()

	FInteractionData() :CurrentInteractableActor(nullptr)
	{

	}

	UPROPERTY()
	AActor* CurrentInteractableActor;

	UPROPERTY()
	float LastInteractionCheckTime;
};



UCLASS()
class PROJECTUR_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

	
public:
	ABaseCharacter();


protected:
	virtual void BeginPlay() override;



	//==================================================================================
	// Camera
	//==================================================================================
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UCameraComponent> FollowCamera;



	//==================================================================================
	// Key Input
	//==================================================================================
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Move(const FInputActionValue& Value);
	virtual void Look(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input , Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UInputAction> InterAction;



	//==================================================================================
	// InterAction
	//==================================================================================
protected:
	UPROPERTY(VisibleAnywhere, Category = "Character | Interaction")
	TScriptInterface<IInteractionInterface> TargetInteractableActor;

	FInteractionData InteractionData;
};
