// Fill out your copyright notice in the Description page of Project Settings.


#include "PCNarbashAnimInstance.h"
#include "PCNarbash.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPCNarbashAnimInstance::NativeInitializeAnimation()
{
	IsOnTransPitchBone = false;
	IsOnTransYawBone = true;
	IsAccelation = false;
	IsInAir = false;

}

void UPCNarbashAnimInstance::NativeUpdateAnimation(float deltaTime)
{
	Super::NativeUpdateAnimation(deltaTime);

	TObjectPtr<APCNarbash> Owner = Cast<APCNarbash>(TryGetPawnOwner());
	if (::IsValid(Owner))
	{
		CurSpeed = Owner->GetVelocity().Size();
		MoveAxis_X = Owner->GetMoveForwardInput() * CurSpeed;
		MoveAxis_Y = Owner->GetMoveRightInput() * CurSpeed;
		IsAccelation = (Owner->GetCharacterMovement()->GetCurrentAcceleration().Length() > 0.f ? true : false);
		IsInAir = Owner->GetCharacterMovement()->IsFalling();

		FRotator Rot = Owner->GetBaseAimRotation() - Owner->GetActorRotation();
		AimPitch = Rot.Pitch;
		AimYaw = Rot.Yaw;

	}

}

void UPCNarbashAnimInstance::PlayNormalAttackMontage(uint8 curCombo)
{
	FName sectionName = FName(FString::Printf(TEXT("Combo%d"), curCombo));

	Montage_Play(NormalAttackMontage, 1.f);
	Montage_JumpToSection(sectionName, NormalAttackMontage);

}

void UPCNarbashAnimInstance::ReadySkillOneMontage()
{
	IsOnTransPitchBone = true;
	Montage_Play(SkillOneMontage);

}

void UPCNarbashAnimInstance::PlaySkillOneMontage()
{
	IsOnTransPitchBone = false;
	Montage_Play(SkillOneMontage);
	Montage_JumpToSection(FName("LoopEnd"), SkillOneMontage);

}

void UPCNarbashAnimInstance::StopSkillOneMontage()
{
	IsOnTransPitchBone = false;
	Montage_Stop(0.5f, SkillOneMontage);

}

void UPCNarbashAnimInstance::ReadySkillTwoMontage()
{
	IsOnTransYawBone = false;
	Montage_Play(SkillTwoMontage);

}

void UPCNarbashAnimInstance::StopSkillTwoMontage()
{
	Montage_Stop(0.3f, SkillTwoMontage);

}

void UPCNarbashAnimInstance::PlayDashMontage(float AnimPlayRate)
{
	Montage_Play(DashMontage, AnimPlayRate);
}

void UPCNarbashAnimInstance::StopDashMontage()
{
	Montage_Stop(0.2f, DashMontage);
}

void UPCNarbashAnimInstance::AnimNotify_AttackEnd()
{
	OnAttackEnd.Broadcast();

}

void UPCNarbashAnimInstance::AnimNotify_NextComboCheck()
{
	OnNextComboCheck.Broadcast();

}

void UPCNarbashAnimInstance::AnimNotify_SkillOneEnd()
{
	OnSkillOneEnd.Broadcast();

}

void UPCNarbashAnimInstance::AnimNotify_SkillTwoStart()
{
	OnSkillTwoStart.Broadcast();

}

void UPCNarbashAnimInstance::AnimNotify_SkillTwoEnd()
{
	IsOnTransYawBone = true;
	OnSkillTwoEnd.Broadcast();

}

void UPCNarbashAnimInstance::AnimNotify_ThrowStick()
{
	OnThrowStick.Broadcast();

}
