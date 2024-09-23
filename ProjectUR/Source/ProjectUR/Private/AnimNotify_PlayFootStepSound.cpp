// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_PlayFootStepSound.h"
#include "FootStepSoundList.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

UAnimNotify_PlayFootStepSound::UAnimNotify_PlayFootStepSound()
{
	CheckDistance = 10.0f;

}

void UAnimNotify_PlayFootStepSound::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	FootStep(MeshComp);
}

void UAnimNotify_PlayFootStepSound::FootStep(USkeletalMeshComponent* MeshComp)
{
	if (SoundListAsset == nullptr)
	{
		return;
	}

	SoundList = Cast<UFootStepSoundList>(SoundListAsset->GetDefaultObject());
	if (SoundList == nullptr)
	{
		return;
	}

	FTransform FootTransform = MeshComp->GetSocketTransform(SocketName);
	FVector LineTrace_Start = FootTransform.GetLocation();
	FVector LineTrace_End = FootTransform.GetLocation() - FVector::UpVector * CheckDistance;

	FHitResult HitResult;
	TArray<AActor*> Ignore;
	Ignore.Add(MeshComp->GetOwner());
	bool bResult = false;
	bResult = UKismetSystemLibrary::LineTraceSingle(MeshComp->GetWorld(), LineTrace_Start, LineTrace_End, UEngineTypes::ConvertToTraceType(ECC_WorldStatic), true, Ignore, EDrawDebugTrace::None, HitResult, true);

	if (bResult)
	{
		if (HitResult.GetActor() == nullptr) { return; }

		USoundBase* pSound = SoundList->GetSound(HitResult.PhysMaterial->GetName());
		if (pSound == nullptr) { return; }

		UGameplayStatics::SpawnSoundAttached(pSound, MeshComp, SocketName, FVector(ForceInit), EAttachLocation::SnapToTarget, false, VolumeMultiplier, PitchMultiplier);
	}
}
