// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "../09_Enums/PlayerEnum.h"
#include "../04_Actor/01_InteractableActor/InteractionInterface.h"
#include "LevelUpCardData.h"
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
class PROJECTUR_API ABaseCharacter : public ACharacter, public CLevelUpCardData
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




	//==================================================================================
	// InterAction
	//==================================================================================
protected:
	UPROPERTY(VisibleAnywhere, Category = "Character | Interaction")
	TScriptInterface<IInteractionInterface> TargetInteractableActor;

	FInteractionData InteractionData;


};
