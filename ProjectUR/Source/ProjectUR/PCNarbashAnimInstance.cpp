// Fill out your copyright notice in the Description page of Project Settings.


#include "PCNarbashAnimInstance.h"
#include "02_Player/PCNarbash.h"
#include "GameFramework/CharacterMovementComponent.h"

UPCNarbashAnimInstance::UPCNarbashAnimInstance()
{
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

void UPCNarbashAnimInstance::PlaySkill1Montage()
{
	Montage_Play(Skiil1Montage);
}

void UPCNarbashAnimInstance::AnimNotify_AttackEnd()
{
	OnAttackEnd.Broadcast();

}

void UPCNarbashAnimInstance::AnimNotify_NextComboCheck()
{
	OnNextComboCheck.Broadcast();

}

void UPCNarbashAnimInstance::AnimNotify_Skill1End()
{
	OnSkill1End.Broadcast();

}
