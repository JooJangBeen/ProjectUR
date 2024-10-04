// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseCharacter.h"
#include "TeraCharacter.generated.h"

UCLASS()
class PROJECTUR_API ATeraCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATeraCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

//=====================================================================================
// Load & Prepare Something
//=====================================================================================
	void SetupDefault();
	void LoadMeshAnimation();
	void LoadEnhancedInput();
	void BindInputAction2Fuction(UInputComponent* PlayerInputComponent);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Move(const FInputActionValue& Value);
	virtual void Look(const FInputActionValue& Value);
	virtual void Jump() override;
	void NormalAttack();


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UInputAction> JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> NormalAttackAction;

public:
	float GetMoveForwardInput() { return MoveForwardInput; };
	float GetMoveRightInput() { return MoveRightInput; };
	int32 GetJumpCount() { return JumpCurrentCount; };
	bool GetIsTurn() { return bIsTurn; };
	float NormalizeYaw(float Yaw);
	float CalculateYaw(float DestYaw, float SourYaw);

private:	
	FVector2D OldDirVector;

	float MoveForwardInput;
	float MoveRightInput;

	bool IsAttacking;
	bool bPressAttack;
	bool bIsTurn;
	float TurnTimer;
	
	
};
