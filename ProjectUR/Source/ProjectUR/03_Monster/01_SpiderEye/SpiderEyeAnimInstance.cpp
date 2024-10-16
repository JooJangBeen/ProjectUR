// Fill out your copyright notice in the Description page of Project Settings.


#include "SpiderEyeAnimInstance.h"

void USpiderEyeAnimInstance::NativeInitializeAnimation()
{

	Super::NativeInitializeAnimation();

	AnimIK = NewObject<UAnimIK>(this, UAnimIK::StaticClass());
	AnimIK->InitializeIK(GetSkelMeshComponent(),10.f);

	AnimIK->AddIkBone("left_leg1_4",  500, -300, 3);
	AnimIK->AddIkBone("left_leg2_4",  500, -300, 3);
	AnimIK->AddIkBone("left_leg3_4",  500, -300, 3);
	AnimIK->AddIkBone("left_leg4_4",  500, -300, 3);
	AnimIK->AddIkBone("right_leg1_4", 500, -300, 3);
	AnimIK->AddIkBone("right_leg2_4", 500, -300, 3);
	AnimIK->AddIkBone("right_leg3_4", 500, -300, 3);
	AnimIK->AddIkBone("right_leg4_4", 500, -300, 3);

}

void USpiderEyeAnimInstance::NativeUpdateAnimation(float deltaTime)
{
	Super::NativeUpdateAnimation(deltaTime);


	AnimIK->UpdateIK(deltaTime);
}

