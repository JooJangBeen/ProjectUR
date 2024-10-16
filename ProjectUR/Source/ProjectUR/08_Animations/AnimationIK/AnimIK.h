// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimIK.generated.h"


USTRUCT()
struct FIKTraceData
{
	GENERATED_USTRUCT_BODY()

	FIKTraceData(){	}

	FName BoneName;
	float radius;
	float TopSideOffset;
	float BellowSideOffset;
};
/**
 * 
 */
UCLASS()
class PROJECTUR_API UAnimIK : public UObject
{
	GENERATED_BODY()

public:
	UAnimIK();
	~UAnimIK();

public:
	void InitializeIK(USkeletalMeshComponent* pSkeletalMeshComp, float MeshUpOffset = 0 , float interpspeed = 15.f, bool FootRotate = true);
	void UpdateIK(float DeltaSeconds);

public:
	bool AddIkBone(FName bonename, float TopSideOffset = 30.f, float BellowSideOffset = -30.f, float radius = 3.f);

	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IK", Meta = (AllowPrivateAccess = true))
	TMap<FName, FVector> IKGoalPositionOffSets;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IK", Meta = (AllowPrivateAccess = true))
	TMap<FName, FRotator> IKRotateOffSets;


private:
	FVector CaculateActorBottom();

private:
	TMap<FName, FIKTraceData> BoneIndexs;
	TObjectPtr<class USkeletalMeshComponent> SkeletalMeshComp;
	float InterpSpeed;
	float MeshUpOffset;
	bool bFootRotate;
};
