// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseCharacter.h"
//#include "GameplayTagContainer.h"
#include "GameplayAbilitySpec.h"
#include "PCNarbash.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTUR_API APCNarbash : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	/* Constructor */
	APCNarbash();

protected:
	virtual void BeginPlay() override;

protected:
	/* Setup Func */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void SetupComponents();
	virtual void SetupProperties();
	virtual void SetupAttributes();
	virtual void SetupAbilities();
	virtual void SetupNotifys();
	virtual void SetupMappingContext();

protected:
	/* Behavior Func */
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

public:
	/* Get InputData*/
	float GetMoveForwardInput();
	float GetMoveRightInput();

public:
	/* Get Component */
	class UPCNarbashAnimInstance* GetAnimInstance();

private:
	/* Key Bind Property */
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
	/* Action State Property */
	float MoveForwardInput;
	float MoveRightInput;

	bool IsAttacking;
	bool bReadySkillOne;
	bool bPressAttack;

private:
	/* Player Skill State Property / if Skill state class is implemented, move data */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Skill Info", Meta = (AllowPrivateAccess = true, ClampMin = 0.1f))
	float MaxDashPlayTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Skill Info", Meta = (AllowPrivateAccess = true, ClampMin = 0.1f))
	float DashDist;

	float CurDashPlayTime;
	float DashMoveValue;

private:
	/* Timer Property */
	FTimerHandle DashTimer;
	FTimerHandle DashEndTimer;
	FTimerHandle SkillTwoReadyTimer;

private:
	/* Restricted Action Key Property */
	bool bCamYawLock;
	bool bCamPitchLock;
	bool bMoveFBLock;
	bool bMoveLRLock;
	bool bJumpingLock;
	
private:
	/* Dash Skill Property */
	FRotator DashStartControllerRot;
	FRotator DashStartPlayerRot;
	float ControllerRotLerpRate;
	float SkillTwoDecSpeedLerpRate;

private:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags", Meta = (AllowPrivateAccess = true))
	//FGameplayTagContainer CharacterTags;

	/*
		Tag 적용 예제 코드
	*/
	void InitCharacterTags();
	void IsKnockDown();
	void EndKnockDown();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill", Meta = (AllowPrivateAccess = true))
	TSubclassOf<class ANarbashStick> StickActorClass;

	TObjectPtr<class ANarbashStick> StickActor;

private:
	/* GAS Property */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GAS", Meta = (AllowPrivateAccess = ture))
	TObjectPtr<class UPlayerAttributeSet> PlayerAttributeSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AbilitySystem, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCTAbilitySystemComponent> AbilitySystemComponent;

	FGameplayAbilitySpecHandle NormalAttackAbilityHandle;

private:
	/* Components Property */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Anim, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPCNarbashAnimInstance> PCAnimInstance;
	
};
