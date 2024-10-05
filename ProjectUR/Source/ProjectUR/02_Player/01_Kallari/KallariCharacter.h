// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseCharacter.h"
#include "KallariCharacter.generated.h"

/**
 * 
 */

enum class EKallariInputAction : uint8
{
	MoveAction, LookAction, JumpAction,
	GroundComboAtk, SkillEDAction, SkillSSBAction, SkillAHAAction,
	END
};

#define KallariDefault_MaxWalkSpped 600.f
#define KallariDefault_MinAnalogWalkSpeed 20.f
#define KallariDefault_BrakingDecelerationWalking 10.f
#define KallariDefault_JumpZVelocity 600.f
#define KallariDefault_AirControl 0.35f

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
// Functions to be executed in the tick function
//=====================================================================================
	void CheckDagger(float DeltaSeconds);
	void RestrictMove(float DeltaSeconds);

//=====================================================================================
// Input
//=====================================================================================
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	virtual void Jump() override;
	void GroundComboAtk(const FInputActionValue& Value);
	void Skill_ED(const FInputActionValue& Value);
	void Skill_SSB(const FInputActionValue& Value);
	void Skill_AHA(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"));
	TArray<TObjectPtr<class UInputAction>> InputActionArray;


private:
	TSubclassOf<class AKallariDagger> EclipseDagger;

//=====================================================================================
// For Animation Control
//=====================================================================================
public:
	void Setup_SkillAnimNotify();
	void Setup_MoveRestrictAnimNotify();
	float GetMoveForwardInput() {	return MoveForwardInput;};
	float GetMoveRightInput() { return MoveRightInput; };
	int32 GetJumpCount() { return JumpCurrentCount; };
	bool GetIsTurn() { return bIsTurn; };
	void UpdateCameraZoom();

	float NormalizeYaw(float Yaw);
	float CalculateYaw(float DestYaw, float SourYaw);

private:
	TObjectPtr<class UKallariAnimInstance> pAnimInstance;

	FVector2D OldDirVector;

	float MoveForwardInput;
	float MoveRightInput;

	bool bIsTurn;
	float TurnTimer;

	int8 GroundComboAtkCount;
	int8 iGroundComboChecker;

	bool bDashMove;
	float BlickCameraTimer;
	bool bRestrictMove;
	FVector RestrictMoveDir;
	FVector BlinkTargetPos;
	float RestrictMoveSpeed;
	float TargetArmLength;
	float StartArmLength;
	float InterpSpeed;   
	FTimerHandle CameraLagTimerHandle;

	TObjectPtr<class AKallariDagger> TargettedDagger;
	bool bTargettedDagger;
	bool bNeedToCheckDagger;

private:
	/* Restricted Action Key */
	bool bCamYawLock;
	bool bCamPitchLock;
	bool bMoveFBLock;
	bool bMoveLRLock;
	bool bMoveBLock;
	bool bJumpingLock;
};
