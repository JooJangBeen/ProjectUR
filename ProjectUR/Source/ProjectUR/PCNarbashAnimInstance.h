// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PCNarbashAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEnd);
DECLARE_MULTICAST_DELEGATE(FOnNextComboCheck);
DECLARE_MULTICAST_DELEGATE(FOnSkill1End);

/**
 * 
 */
UCLASS()
class PROJECTUR_API UPCNarbashAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPCNarbashAnimInstance();

public:
	virtual void NativeUpdateAnimation(float deltaTime) override;

private:
	/* Anim Montage */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimMontage", Meta = (AllowPrivateAccess = true))
	UAnimMontage* NormalAttackMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimMontage", Meta = (AllowPrivateAccess = true))
	UAnimMontage* Skiil1Montage;

public:
	void PlayNormalAttackMontage(uint8 curComboCombo);
	void PlaySkill1Montage();

public:
	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_NextComboCheck();

	UFUNCTION()
	void AnimNotify_Skill1End();

public:
	/* Anim Notify */
	FOnAttackEnd		OnAttackEnd;
	FOnNextComboCheck	OnNextComboCheck;
	FOnSkill1End		OnSkill1End;

private:
	/* Player Info Value */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", Meta = (AllowPrivateAccess = true))
	float MoveAxis_X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", Meta = (AllowPrivateAccess = true))
	float MoveAxis_Y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", Meta = (AllowPrivateAccess = true))
	bool IsAccelation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", Meta = (AllowPrivateAccess = true))
	bool IsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", Meta = (AllowPrivateAccess = true))
	float CurSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", Meta = (AllowPrivateAccess = true))
	float AimYaw;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", Meta = (AllowPrivateAccess = true))
	float AimPitch;

};
