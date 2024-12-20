// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../../08_Animations/AnimationIK/AnimIK.h"
#include "TerraAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTUR_API UTerraAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
	
public:
	UTerraAnimInstance();

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float deltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IK", Meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimIK> AnimIK;
	
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

	float NormalizeYaw(float Yaw);
};
