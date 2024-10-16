// Fill out your copyright notice in the Description page of Project Settings.


#include "PDSpiderAnimInstance.h"
#include "GameFramework/Character.h"

void UPDSpiderAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();



	AddIkBone("leg_a_06_l", true,	true);
	AddIkBone("leg_b_06_l", true, false);
	AddIkBone("leg_c_06_l", true, true);
	AddIkBone("leg_d_06_l", true, false);

	AddIkBone("leg_a_06_r", false, false);
	AddIkBone("leg_b_06_r", false, true);
	AddIkBone("leg_c_06_r", false, false);
	AddIkBone("leg_d_06_r", false, true);


	LeftFowardSoc = FName("LeftFootNext");
	RightFowardSoc = FName("RightFootNext");

	bFootWalk = false;


	ACharacter* pOwner = Cast<ACharacter>(GetSkelMeshComponent()->GetOwner());
	if (pOwner)
	{
		ActorPrevPos = pOwner->GetActorLocation();
	}

	TargetMoveDist = 60.f;

}

void UPDSpiderAnimInstance::NativeUpdateAnimation(float deltaTime)
{
	Super::NativeUpdateAnimation(deltaTime);

	ACharacter* pOwner = Cast<ACharacter>(GetSkelMeshComponent()->GetOwner());



	if (pOwner)
	{


		float dist = (pOwner->GetActorLocation() - ActorPrevPos).Length();


		if (dist > TargetMoveDist)
		{
			bFootWalk = !bFootWalk;
			ActorPrevPos = pOwner->GetActorLocation();
			dist = 0;
		}


		for (size_t i = 0; i < LeftLegDatas.Num(); i++)
		{

			if (bFootWalk)
			{
				if (i % 2)
				{
					CaculateOffset(LeftLegDatas[i], dist,true);
					CaculateOffset(RightLegDatas[i], dist,false);
				}
				else
				{
					CaculateOffset(RightLegDatas[i], dist,true);
					CaculateOffset(LeftLegDatas[i], dist, false);
				}

			}
			else
			{
				if (i % 2)
				{
					CaculateOffset(RightLegDatas[i], dist, true);
					CaculateOffset(LeftLegDatas[i], dist, false);

				}
				else
				{
					CaculateOffset(LeftLegDatas[i], dist, true);
					CaculateOffset(RightLegDatas[i], dist, false);
				}

			}

		}
	}
}

bool UPDSpiderAnimInstance::AddIkBone(FName bonename, bool bIsLeftLeg,bool bBool)
{
	int32 BoneIndex = GetSkelMeshComponent()->GetBoneIndex(bonename);
	if (BoneIndex == INDEX_NONE)
		return false;
	
	FPDAnimData pdData;

	pdData.BoneName = bonename;

	pdData.Nextfloat = 100;
	pdData.Prevfloat = -100;

	if (bIsLeftLeg)
		LeftLegDatas.Add(pdData);
	else
		RightLegDatas.Add(pdData);

	IKGoalPositionOffSets.Add(pdData.BoneName, FVector(0, 0, 0));

	return true;
}



void UPDSpiderAnimInstance::CaculateOffset(FPDAnimData& animdata, float& dist, bool bBool)
{
	FVector* offset = IKGoalPositionOffSets.Find(animdata.BoneName);

	float Targetfloat = 0;

	if(bBool)
		Targetfloat = FMath::FInterpTo(animdata.Prevfloat, animdata.Nextfloat, 1, (dist / TargetMoveDist) + 0.01f);
	else
		Targetfloat = FMath::FInterpTo(animdata.Nextfloat, animdata.Prevfloat, 1, (dist / TargetMoveDist) + 0.01f);

	*offset = FVector(0, Targetfloat,0);

}
