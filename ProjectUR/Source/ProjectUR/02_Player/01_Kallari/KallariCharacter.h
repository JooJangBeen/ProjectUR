// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseCharacter.h"
#include "KallariCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTUR_API AKallariCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	AKallariCharacter();

//=====================================================================================
// Default Override Fuction
//=====================================================================================
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;


//=====================================================================================
// Load & Prepare Something
//=====================================================================================
	void SetupDefault();
	void LoadMeshAnimation();
	void LoadEnhancedInput();
	void BindInputAction2Fuction(UInputComponent* PlayerInputComponent);

//=====================================================================================
// Input
//=====================================================================================
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Skill_ED(const FInputActionValue& Value);
	void Skill_SSB(const FInputActionValue& Value);
	void Skill_AHA(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UInputAction> JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UInputAction> LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UInputAction> SkillEDAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UInputAction> SkillSSBAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UInputAction> SkillAHAAction;


//=====================================================================================
// For Animation Control
//=====================================================================================
public:
	float GetMoveForwardInput() {	return MoveForwardInput;};
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
};
