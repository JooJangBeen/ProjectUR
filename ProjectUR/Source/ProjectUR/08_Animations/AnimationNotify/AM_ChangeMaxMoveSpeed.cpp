// Fill out your copyright notice in the Description page of Project Settings.


#include "AM_ChangeMaxMoveSpeed.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAM_ChangeMaxMoveSpeed::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	TObjectPtr<ACharacter> Owner = Cast<ACharacter>(MeshComp->GetOwner());
	if (Owner)
	{
		Owner->GetCharacterMovement()->MaxWalkSpeed = TargetSpeed;
	}



}
