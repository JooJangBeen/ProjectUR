// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FootStepSoundList.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECTUR_API UFootStepSoundList : public UObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound, Meta = (AllowPrivateAccess = true))
	TMap<FString, TObjectPtr<class USoundBase>> SoundList;

public:
	TObjectPtr<class USoundBase> GetSound(FString SoundName);

	int GetSoundListNum();

};
