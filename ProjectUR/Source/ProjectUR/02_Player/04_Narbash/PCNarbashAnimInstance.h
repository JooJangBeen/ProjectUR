// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PCNarbashAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEnd);
DECLARE_MULTICAST_DELEGATE(FOnNextComboCheck);
DECLARE_MULTICAST_DELEGATE(FOnSkillOneEnd);
DECLARE_MULTICAST_DELEGATE(FOnSkillTwoStart);
DECLARE_MULTICAST_DELEGATE(FOnSkillTwoEnd);
DECLARE_MULTICAST_DELEGATE(FOnThrowStick);

/**
 * 
 */
UCLASS()
class PROJECTUR_API UPCNarbashAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float deltaTime) override;

private:
	/* Anim Montage */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimMontage", Meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> NormalAttackMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimMontage", Meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> SkillOneMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimMontage", Meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> SkillTwoMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimMontage", Meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> DashMontage;

public:
	void PlayNormalAttackMontage(uint8 curComboCombo);
	void ReadySkillOneMontage();
	void PlaySkillOneMontage();
	void StopSkillOneMontage();
	void ReadySkillTwoMontage();
	void StopSkillTwoMontage();
	void PlayDashMontage(float AnimPlayRate = 1.f);
	void StopDashMontage();

public:
	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_NextComboCheck();

	UFUNCTION()
	void AnimNotify_SkillOneEnd();

	UFUNCTION()
	void AnimNotify_SkillTwoStart();

	UFUNCTION()
	void AnimNotify_SkillTwoEnd();

	UFUNCTION()
	void AnimNotify_ThrowStick();

public:
	/* Anim Notify */
	FOnAttackEnd		OnAttackEnd;
	FOnNextComboCheck	OnNextComboCheck;
	FOnSkillOneEnd		OnSkillOneEnd;
	FOnSkillTwoStart	OnSkillTwoStart;
	FOnSkillTwoEnd		OnSkillTwoEnd;
	FOnThrowStick		OnThrowStick;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", Meta = (AllowPrivateAccess = true))
	bool IsOnTransPitchBone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", Meta = (AllowPrivateAccess = true))
	bool IsOnTransYawBone;

};
