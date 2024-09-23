// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_PlayFootStepSound.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTUR_API UAnimNotify_PlayFootStepSound : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UAnimNotify_PlayFootStepSound();
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	void FootStep(USkeletalMeshComponent* MeshComp);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify", meta = (DisplayName = "SoundListAsset"))
	TSubclassOf<class UFootStepSoundList> SoundListAsset;

	UPROPERTY()
	TObjectPtr<class UFootStepSoundList> SoundList;

public:
	/* Setting */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify")
	float VolumeMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify")
	float PitchMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify")
	float CheckDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify")
	FName SocketName;

};
