// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../../08_Animations/AnimationIK/AnimIK.h"
#include "SpiderEyeAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTUR_API USpiderEyeAnimInstance : public UAnimInstance 
{
	GENERATED_BODY()


public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float deltaTime) override;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IK", Meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimIK> AnimIK;
};
