// Fill out your copyright notice in the Description page of Project Settings.


#include "FootStepSoundList.h"

TObjectPtr<class USoundBase> UFootStepSoundList::GetSound(FString SoundName)
{
	if(SoundList.Contains(SoundName))
	{
			return SoundList[SoundName];
	}
	
	return nullptr;
}

int UFootStepSoundList::GetSoundListNum()
{
	return SoundList.Num();
}
