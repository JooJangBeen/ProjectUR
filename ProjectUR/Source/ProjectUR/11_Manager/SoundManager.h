// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SoundManager.generated.h"

class USoundCue;
/**
 * 
 */
UCLASS()
class PROJECTUR_API USoundManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
protected:
	virtual void Initialize(FSubsystemCollectionBase& collrection) override;

public:
	//배경음악 재생
	void PlayBackGroundMusic(USoundCue* musicCue, float fadeinDuration = 0.5f);

	//SFX사운드 재생
	void PlaySFX(USoundCue* sfxMusicCue, float volume = 1.0f);
	//UI사운드 재생
	void PlayUISound(USoundCue* uiSoundCue, float volume = 1.0f);


	void SetBackGroundMusicVolume(float volume);
	void SetSFXVolume(float volume);
	void SetUIVolume(float volume);

	void FadeOutBackGroundMusic(float fadeOutDuration);
	void FadeInBackGroundMusic(float fadeInDuration);

private:
	
	float mSfxVolume = 1.0f;
	float mUiVolume = 1.0f;
	float mBackgroundVolume = 1.0f;

	UPROPERTY()
	UAudioComponent* mCurrentBackGroundMusic;
	
};
