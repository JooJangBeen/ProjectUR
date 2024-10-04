// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GrimAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTUR_API UGrimAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UGrimAnimInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float deltaTime) override;
};
