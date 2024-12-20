// Fill out your copyright notice in the Description page of Project Settings.


#include "KallariAnimInstance.h"
#include "KallariCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math.h"

UKallariAnimInstance::UKallariAnimInstance()
{
	IsAccelation = false;
	IsInAir = false;

	
	//for (int i = 0; i< int(EKallariAnimNotify::END); i++)
	//	AnimNotifyArray.Add(FOnAnimNofityEx());
	AnimNotifyArray.SetNum(int(EKallariAnimNotify::END));
	
}

float NormalizeYaw(float Yaw)
{
	while (Yaw > 180.0f) Yaw -= 360.0f;
	while (Yaw < -180.0f) Yaw += 360.0f;
	return Yaw;
}

void UKallariAnimInstance::NativeInitializeAnimation()
{

	Super::NativeInitializeAnimation();
	//foot_l
	//foot_r
	AnimIK = NewObject<UAnimIK>(this, UAnimIK::StaticClass());
	AnimIK->InitializeIK(GetSkelMeshComponent(), 10.f,10.f,true);


	AnimIK->AddIkBone("foot_l", 40, -60, 3);
	AnimIK->AddIkBone("foot_r", 40, -60, 3);
}

void UKallariAnimInstance::NativeUpdateAnimation(float deltaTime)
{
	Super::NativeUpdateAnimation(deltaTime);

	AnimIK->UpdateIK(deltaTime);

	TObjectPtr<class AKallariCharacter> Owner = Cast<AKallariCharacter>(TryGetPawnOwner());


	if (::IsValid(Owner))
	{
		CurSpeed = Owner->GetVelocity().Size();
		MoveAxis_X = Owner->GetMoveForwardInput() * CurSpeed;
		MoveAxis_Y = Owner->GetMoveRightInput() * CurSpeed;
		IsAccelation = (Owner->GetCharacterMovement()->GetCurrentAcceleration().Length() > 0.f ? true : false);
		IsInAir = Owner->GetCharacterMovement()->IsFalling();
		JumpCount = Owner->GetJumpCount();
		IsTurn = Owner->GetIsTurn();

		FRotator Rot = Owner->GetBaseAimRotation() - Owner->GetActorRotation();
		AimPitch = Rot.Pitch;
		AimYaw = NormalizeYaw(Rot.Yaw);

	}

}

FOnAnimNofityEx* const UKallariAnimInstance::GetAnimNotifyDeligate(EKallariAnimNotify eNotify)
{
	check(int(eNotify) < int(EKallariAnimNotify::END));
	return &AnimNotifyArray[int(eNotify)];
}

UAnimMontage* const UKallariAnimInstance::GetAnimMontage(EKallariMTG eMtg)
{
	check(int(eMtg) < int(EKallariMTG::END));
	return AnimMontage[int(eMtg)];
}


void UKallariAnimInstance::PlayAnimMontage(EKallariMTG eMtg, float PlayRate)
{
	if (!IsAnyMontagePlaying() || Montage_IsPlaying(AnimMontage[int(eMtg)]))
	{
		Montage_Play(AnimMontage[int(eMtg)], PlayRate);
	}
}

void UKallariAnimInstance::PlayAnimMontage(EKallariMTG eMtg, FName sectionName, float PlayRate)
{
	if (!IsAnyMontagePlaying() || Montage_IsPlaying(AnimMontage[int(eMtg)]))
		Montage_Play(AnimMontage[int(eMtg)], PlayRate);
	if (Montage_GetCurrentSection(AnimMontage[int(eMtg)]) != sectionName)
	{
		Montage_Play(AnimMontage[int(eMtg)], PlayRate);
		Montage_JumpToSection(sectionName, AnimMontage[int(eMtg)]);
	}
}

void UKallariAnimInstance::StopAnimMontage(EKallariMTG eMtg, float InOutBlendTime)
{
	Montage_Stop(InOutBlendTime, AnimMontage[int(eMtg)]);
}



