// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PDSpiderAnimInstance.generated.h"



USTRUCT()
struct FPDAnimData
{
	GENERATED_USTRUCT_BODY()

	FPDAnimData() {	}

	FName BoneName;

	float Nextfloat;
	float Prevfloat;
};
/**
 * 
 */
UCLASS()
class PROJECTUR_API UPDSpiderAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	


public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float deltaTime) override;




public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IK", Meta = (AllowPrivateAccess = true))
	TMap<FName, FVector> IKGoalPositionOffSets;

private:
	bool AddIkBone(FName bonename, bool bIsLeftLeg, bool bBool);
	void CaculateOffset(FPDAnimData& animdata,float& dist,bool bBool);


private:
	TArray<FPDAnimData> LeftLegDatas;
	TArray<FPDAnimData> RightLegDatas;

	FName LeftFowardSoc;
	FName RightFowardSoc;

	bool bFootWalk;
	FVector ActorPrevPos;
	float	TargetMoveDist;
};
