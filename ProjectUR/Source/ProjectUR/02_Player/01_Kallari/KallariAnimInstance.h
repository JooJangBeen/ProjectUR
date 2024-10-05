// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "KallariAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAnimNofityEx);
/**
 * 
 */

UENUM(BlueprintType)
enum class EKallariMTG : uint8
{
	GroundComboAtk UMETA(DisplayName = "GroundComboAtk"),
	EclipseDagger UMETA(DisplayName = "EclipseDagger"),
	ShadowStep UMETA(DisplayName = "ShadowStep"),
	Blink UMETA(DisplayName = "Blink"),
	Annihilation UMETA(DisplayName = "Annihilation"),
	LevelStart UMETA(DisplayName = "LevelStart"),
	ReCall UMETA(DisplayName = "ReCall"),
	Respawn UMETA(DisplayName = "Respawn"),
	END
};

enum class EKallariAnimNotify : uint8
{
	BlockMoveFB, BlockMoveB, BlockMoveLR, BlockJump, BlockCameraYaw, BlockCameraPitch,
	BlockAllMove, BlockAllMoveJump, BlockAllCameraCtrl,BlocakAll,
	UnBlockMoveFB, UnBlockMoveB,UnBlockMoveLR, UnBlockJump, UnBlockCameraYaw, UnBlockCameraPitch, UnBlockAll,

	CheckNextCombo,	PlayNextCombo,	StopComboAtk,
	ShadowStepStart, ShadowStepEnd ,AimDagger, DeAimDagger, ThrowDagger,
	BlinkCameraLagSet, BlinkMoveFwd,  BlinkTeleport, BlinkEnd,
	AnhilSetup, AnhilNextSlot, AnhilTeleport, AnhilCamLagEnd, AnhilEnd,
	END
};


UCLASS()
class PROJECTUR_API UKallariAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	

public:
	UKallariAnimInstance();

public:
	virtual void NativeUpdateAnimation(float deltaTime) override;

public:
	UAnimMontage* const GetAnimMontage(EKallariMTG eMtg);
	FOnAnimNofityEx* const GetAnimNotifyDeligate(EKallariAnimNotify eNotify);
	void BroadCastAnimNotify(EKallariAnimNotify eNotify) { AnimNotifyArray[int(eNotify)].Broadcast(); };
	void PlayAnimMontage(EKallariMTG eMtg, float PlayRate = 1.f);
	void PlayAnimMontage(EKallariMTG eMtg, FName sectionName, float PlayRate = 1.f);
	void StopAnimMontage(EKallariMTG eMtg, float InOutBlendTime = 0.2f);

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimMontage", Meta = (AllowPrivateAccess = true))
	TArray<TObjectPtr<UAnimMontage>> AnimMontage;



#pragma region MoveRestrictAnimNotify
	UFUNCTION()
	void AnimNotify_BlockMoveFB() { AnimNotifyArray[int(EKallariAnimNotify::BlockMoveFB)].Broadcast(); };
	UFUNCTION()
	void AnimNotify_BlockMoveLR() { AnimNotifyArray[int(EKallariAnimNotify::BlockMoveLR)].Broadcast(); };
	UFUNCTION()
	void AnimNotify_BlockJump() { AnimNotifyArray[int(EKallariAnimNotify::BlockJump)].Broadcast(); };
	UFUNCTION()
	void AnimNotify_BlockCameraYaw() { AnimNotifyArray[int(EKallariAnimNotify::BlockCameraYaw)].Broadcast(); };
	UFUNCTION()
	void AnimNotify_BlockCameraPitch() { AnimNotifyArray[int(EKallariAnimNotify::BlockCameraPitch)].Broadcast(); };
	UFUNCTION()
	void AnimNotify_UnBlockMoveFB() { AnimNotifyArray[int(EKallariAnimNotify::UnBlockMoveFB)].Broadcast(); };
	UFUNCTION()
	void AnimNotify_UnBlockMoveLR() { AnimNotifyArray[int(EKallariAnimNotify::UnBlockMoveLR)].Broadcast(); };
	UFUNCTION()
	void AnimNotify_UnBlockJump() { AnimNotifyArray[int(EKallariAnimNotify::UnBlockJump)].Broadcast(); };
	UFUNCTION()
	void AnimNotify_UnBlockCameraYaw() { AnimNotifyArray[int(EKallariAnimNotify::UnBlockCameraYaw)].Broadcast(); };
	UFUNCTION()
	void AnimNotify_UnBlockCameraPitch() { AnimNotifyArray[int(EKallariAnimNotify::UnBlockCameraPitch)].Broadcast(); };
	UFUNCTION()
	void AnimNotify_UnBlockAll() { AnimNotifyArray[int(EKallariAnimNotify::UnBlockAll)].Broadcast(); };
	UFUNCTION()
	void AnimNotify_BlockAllMove() { AnimNotifyArray[int(EKallariAnimNotify::BlockAllMove)].Broadcast(); };
	UFUNCTION()
	void AnimNotify_BlockCameraCtrl() { AnimNotifyArray[int(EKallariAnimNotify::BlockAllCameraCtrl)].Broadcast(); };
	UFUNCTION()
	void AnimNotify_BlocakAll() { AnimNotifyArray[int(EKallariAnimNotify::BlocakAll)].Broadcast(); };
	UFUNCTION()
	void AnimNotify_BlockAllMoveJump() { AnimNotifyArray[int(EKallariAnimNotify::BlockAllMoveJump)].Broadcast(); };
	UFUNCTION()
	void AnimNotify_BlockMoveB() { AnimNotifyArray[int(EKallariAnimNotify::BlockMoveB)].Broadcast(); };
	UFUNCTION()
	void AnimNotify_UnBlockMoveB() { AnimNotifyArray[int(EKallariAnimNotify::UnBlockMoveB)].Broadcast(); };
#pragma endregion

#pragma region SkillAnimNotify
private:
	UFUNCTION()
	void AnimNotify_AimDagger() { AnimNotifyArray[int(EKallariAnimNotify::AimDagger)].Broadcast(); };
	UFUNCTION()
	void AnimNotify_DeAimDagger() { AnimNotifyArray[int(EKallariAnimNotify::DeAimDagger)].Broadcast(); }
	UFUNCTION()
	void AnimNotify_ThrowDagger() { AnimNotifyArray[int(EKallariAnimNotify::ThrowDagger)].Broadcast(); }
	
	UFUNCTION()
	void AnimNotify_CheckNextCombo() { 	AnimNotifyArray[int(EKallariAnimNotify::CheckNextCombo)].Broadcast();}
	UFUNCTION()
	void AnimNotify_PlayNextCombo() { AnimNotifyArray[int(EKallariAnimNotify::PlayNextCombo)].Broadcast(); }
	UFUNCTION()
	void AnimNotify_StopComboAtk() { AnimNotifyArray[int(EKallariAnimNotify::StopComboAtk)].Broadcast(); }

	UFUNCTION()
	void AnimNotify_ShadowStepStart() { AnimNotifyArray[int(EKallariAnimNotify::ShadowStepStart)].Broadcast(); }
	UFUNCTION()
	void AnimNotify_ShadowStepEnd() { AnimNotifyArray[int(EKallariAnimNotify::ShadowStepEnd)].Broadcast(); }

	UFUNCTION()
	void AnimNotify_BlinkCameraLagSet() { AnimNotifyArray[int(EKallariAnimNotify::BlinkCameraLagSet)].Broadcast(); }
	UFUNCTION()
	void AnimNotify_BlinkMoveFwd() { AnimNotifyArray[int(EKallariAnimNotify::BlinkMoveFwd)].Broadcast(); }
	UFUNCTION()
	void AnimNotify_BlinkTeleport() { AnimNotifyArray[int(EKallariAnimNotify::BlinkTeleport)].Broadcast(); }
	UFUNCTION()
	void AnimNotify_BlinkEnd() { AnimNotifyArray[int(EKallariAnimNotify::BlinkEnd)].Broadcast(); }

	UFUNCTION()
	void AnimNotify_AnhilSetup() { AnimNotifyArray[int(EKallariAnimNotify::AnhilSetup)].Broadcast(); }
	UFUNCTION()
	void AnimNotify_AnhilNextSlot() { AnimNotifyArray[int(EKallariAnimNotify::AnhilNextSlot)].Broadcast(); }
	UFUNCTION()
	void AnimNotify_AnhilTeleport() { AnimNotifyArray[int(EKallariAnimNotify::AnhilTeleport)].Broadcast(); }
	UFUNCTION()
	void AnimNotify_AnhilCamLagEnd() { AnimNotifyArray[int(EKallariAnimNotify::AnhilCamLagEnd)].Broadcast(); }
	UFUNCTION()
	void AnimNotify_AnhilEnd() { AnimNotifyArray[int(EKallariAnimNotify::AnhilEnd)].Broadcast(); }

#pragma endregion

private:
	TArray<FOnAnimNofityEx> AnimNotifyArray;


#pragma region PlayerInfoValue
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
	bool IsTurn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", Meta = (AllowPrivateAccess = true))
	int JumpCount;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", Meta = (AllowPrivateAccess = true))
	float CurSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", Meta = (AllowPrivateAccess = true))
	float AimYaw;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", Meta = (AllowPrivateAccess = true))
	float AimPitch;
#pragma endregion




};
