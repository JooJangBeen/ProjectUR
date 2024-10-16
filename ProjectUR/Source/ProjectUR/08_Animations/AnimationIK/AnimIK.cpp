// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimIK.h"
#include "Components/BoxComponent.h"      
#include "Components/CapsuleComponent.h"  
#include "Components/SphereComponent.h" 
#include "Components/SceneComponent.h" 
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math/UnrealMathUtility.h"

UAnimIK::UAnimIK()
{
}

UAnimIK::~UAnimIK()
{
}

void UAnimIK::InitializeIK(USkeletalMeshComponent* pSkeletalMeshComp, float UpOffset, float interpspeed, bool FootRotate)
{
	check(pSkeletalMeshComp);
	SkeletalMeshComp = pSkeletalMeshComp;

	InterpSpeed = interpspeed;
	bFootRotate = FootRotate;
	MeshUpOffset = UpOffset;
}

void UAnimIK::UpdateIK(float DeltaSeconds)
{
	TObjectPtr<ACharacter> owner = Cast<ACharacter>(SkeletalMeshComp->GetOwner());
	if (!owner)
		return;

	if (owner->GetMovementComponent()->IsFalling())
	{
		FVector offsetTarget = FVector(0, 0, 0);

		for (auto& pair : IKGoalPositionOffSets)
			pair.Value = FMath::VInterpTo(pair.Value, offsetTarget, DeltaSeconds, InterpSpeed);;

		return;
	}
	else
	{
		FVector ActorLocation = CaculateActorBottom();
		FVector BoneLocation;

		FVector TraceStart;
		FVector TraceEnd;
		FVector offsetTarget;
		FHitResult HitResult;
		bool bResult = false;
		UWorld* world = GetWorld();

		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(SkeletalMeshComp->GetOwner());
		CollisionParams.bTraceComplex = true;
		CollisionParams.bReturnPhysicalMaterial = false;


		if (world)
		{
			for (auto& pair : BoneIndexs)
			{
				//위치 값 수정
				BoneLocation = SkeletalMeshComp->GetBoneLocation(pair.Value.BoneName);
				//BoneLocation.Z += MeshUpOffset;
				TraceStart = FVector(BoneLocation.X, BoneLocation.Y, ActorLocation.Z + pair.Value.TopSideOffset);
				TraceEnd = FVector(BoneLocation.X, BoneLocation.Y, ActorLocation.Z + pair.Value.BellowSideOffset);
				FCollisionShape SphereShape = FCollisionShape::MakeSphere(pair.Value.radius);

				bResult = world->SweepSingleByChannel(HitResult, TraceStart, TraceEnd, FQuat::Identity, ECC_WorldDynamic, SphereShape, CollisionParams);


				offsetTarget = FVector(0, 0, 0);
				FVector* offset = IKGoalPositionOffSets.Find(pair.Value.BoneName);


				if (bResult)
				{
					HitResult.ImpactPoint.Z += MeshUpOffset;
					offsetTarget = HitResult.ImpactPoint - FVector(BoneLocation.X, BoneLocation.Y, ActorLocation.Z);
				}
				

				*offset = FMath::VInterpTo(*offset, offsetTarget, DeltaSeconds, InterpSpeed);

				if ((BoneLocation + *offset).Z < HitResult.ImpactPoint.Z)
					*offset = offsetTarget;

				//회전 값 수정
				if (bFootRotate)
				{
					FRotator* Rotoffset = IKRotateOffSets.Find(pair.Value.BoneName);

					*Rotoffset = FRotator(0, 0, 0);

					if (bResult)
					{
						FVector FootForward = SkeletalMeshComp->GetBoneAxis(pair.Value.BoneName, EAxis::Y).GetSafeNormal();
						float DotProduct = FVector::DotProduct(FootForward, FVector(0, 1, 0));

						*Rotoffset = FRotator(
							FMath::RadiansToDegrees(FMath::Atan2(HitResult.Normal.X, HitResult.Normal.Z)),	0,
							FMath::RadiansToDegrees(FMath::Atan2(HitResult.Normal.Y, HitResult.Normal.Z)) * DotProduct);
					}

				}
			}
		}
	}
}

bool UAnimIK::AddIkBone(FName bonename, float TopSideOffset, float BellowSideOffset , float radius)
{
	check(SkeletalMeshComp);

	FIKTraceData tIkData;

	int32 BoneIndex = SkeletalMeshComp->GetBoneIndex(bonename);
	if (BoneIndex == INDEX_NONE)
		return false;


	tIkData.BoneName = bonename;
	tIkData.TopSideOffset = TopSideOffset;
	tIkData.BellowSideOffset = BellowSideOffset;
	tIkData.radius = radius;

	BoneIndexs.Add(bonename, tIkData);
	IKGoalPositionOffSets.Add(tIkData.BoneName, FVector());

	if(bFootRotate)
		IKRotateOffSets.Add(tIkData.BoneName, FRotator());

	return true;
}

FVector UAnimIK::CaculateActorBottom()
{
	check(SkeletalMeshComp);
	USceneComponent* RootComp = SkeletalMeshComp->GetOwner()->GetRootComponent();

	FVector result;

	if (UBoxComponent* BoxComp = Cast<UBoxComponent>(RootComp))
	{
		result = BoxComp->GetComponentLocation();
		result.Z -= BoxComp->GetScaledBoxExtent().Z;
	}
	else if (UCapsuleComponent* CapsuleComp = Cast<UCapsuleComponent>(RootComp))
	{
		result = CapsuleComp->GetComponentLocation();
		result.Z -= CapsuleComp->GetScaledCapsuleHalfHeight();
	}
	else if (USphereComponent* SphereComp = Cast<USphereComponent>(RootComp))
	{
		result = SphereComp->GetComponentLocation();
		result.Z -= SphereComp->GetScaledSphereRadius();
	}
	else
	{
		result = SkeletalMeshComp->GetOwner()->GetActorLocation();
	}

	//result.Z -= MeshUpOffset;

	return result;
}
