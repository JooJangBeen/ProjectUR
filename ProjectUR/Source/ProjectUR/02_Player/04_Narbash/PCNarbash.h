// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseCharacter.h"
#include "PCNarbash.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTUR_API APCNarbash : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	APCNarbash();

protected:
	virtual void BeginPlay() override;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void InitProperties();
	virtual void InitCameraSetting();
	virtual void SetupNotifys();
	virtual void Move(const FInputActionValue& Value);
	virtual void Look(const FInputActionValue& Value);
	virtual void Jump() override;
	virtual void StopJumping() override;

	void NormalAttack();
	void DashStart();
	void Dash();
	void ReadySkillOne();
	void StopSkillOne();
	void ThrowStick();
	void ReadySkillTwo();
	void SkillTwoPrePose();
	void StopSkillTwo();

private:
	void InitMappingContextSetting();

public:
	float GetMoveForwardInput();
	float GetMoveRightInput();

private:
	/* Relate Key Bind */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> NormalAttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> SkillOneAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> SkillTwoAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> DashAction;

private:
	float MoveForwardInput;
	float MoveRightInput;

	bool IsAttacking;
	bool bReadySkillOne;
	bool bPressAttack;

private:
	/* Relate Player State / if state class is implemented, move data */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player State", Meta = (AllowPrivateAccess = true))
	uint8 MaxCombo;
	
	uint8 CurCombo;

private:
	/* Relate Player Skill State / if Skill state class is implemented, move data */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Skill Info", Meta = (AllowPrivateAccess = true, ClampMin = 0.1f))
	float MaxDashPlayTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Skill Info", Meta = (AllowPrivateAccess = true, ClampMin = 0.1f))
	float DashDist;

	float CurDashPlayTime;
	float DashMoveValue;

private:
	/* Timer */
	FTimerHandle DashTimer;
	FTimerHandle DashEndTimer;
	FTimerHandle SkillTwoReadyTimer;

private:
	/* Restricted Action Key */
	bool bCamYawLock;
	bool bCamPitchLock;
	bool bMoveFBLock;
	bool bMoveLRLock;
	bool bJumpingLock;

private:
	FRotator DashStartControllerRot;
	FRotator DashStartPlayerRot;
	float ControllerRotLerpRate;
	float SkillTwoDecSpeedLerpRate;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill", Meta = (AllowPrivateAccess = true))
	TSubclassOf<class ANarbashStick> StickActorClass;

	TObjectPtr<class ANarbashStick> StickActor;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Anim, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPCNarbashAnimInstance> PCAnimInstance;

};
