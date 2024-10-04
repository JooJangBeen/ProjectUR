// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AM_ChangeMaxMoveSpeed.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTUR_API UAM_ChangeMaxMoveSpeed : public UAnimNotify
{
	GENERATED_BODY()


public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Meta = (AllowPrivateAccess = "true"), Category = "Valuable");
	float TargetSpeed;
};
