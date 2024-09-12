// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundManager.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h" 
#include "Components/AudioComponent.h"

void USoundManager::Initialize(FSubsystemCollectionBase& collrection)
{
	Super::Initialize(collrection);

	mSfxVolume = 1.0f;
	mUiVolume = 1.0f;
	mBackgroundVolume = 1.0f;
	mCurrentBackGroundMusic = nullptr;
}

void USoundManager::PlayBackGroundMusic(USoundCue* musicCue, float fadeinDuration)
{
	if (musicCue == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("is NullPtr BackGroundMusicCue"));
		return;
	}

	if (mCurrentBackGroundMusic != NULL)
	{
		mCurrentBackGroundMusic->FadeOut(fadeinDuration, 0.0f);
	}

	mCurrentBackGroundMusic = UGameplayStatics::SpawnSound2D(this, musicCue, mBackgroundVolume);

	if (mCurrentBackGroundMusic != NULL)
	{
		mCurrentBackGroundMusic->FadeIn(fadeinDuration);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("is NullPtr mCurrentBackGroundMusic AudioComponent"));
		return;
	}
	
}

void USoundManager::PlaySFX(USoundCue* sfxMusicCue, float volume)
{
	if (sfxMusicCue == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("is NullPtr sfxMusicCue"));
		return;
	}

	UGameplayStatics::SpawnSound2D(GetWorld(), sfxMusicCue, mSfxVolume);
}

void USoundManager::PlayUISound(USoundCue* uiSoundCue, float volume)
{
	if (uiSoundCue == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("is NullPtr uiSoundCue"));
		return;
	}

	UGameplayStatics::SpawnSound2D(GetWorld(), uiSoundCue, mUiVolume);
}

void USoundManager::SetBackGroundMusicVolume(float volume)
{
	mBackgroundVolume = FMath::Clamp(volume, 0.0f, 1.0f);  // 0 ~ 1 사이로 제한

	if (mCurrentBackGroundMusic != nullptr)
	{
		mCurrentBackGroundMusic->SetVolumeMultiplier(mBackgroundVolume);
	}
}

void USoundManager::SetSFXVolume(float volume)
{
	mSfxVolume = FMath::Clamp(volume, 0.0f, 1.0f);  // 0 ~ 1 사이로 제한
}

void USoundManager::SetUIVolume(float volume)
{
	mUiVolume = FMath::Clamp(volume, 0.0f, 1.0f);  // 0 ~ 1 사이로 제한
}

void USoundManager::FadeOutBackGroundMusic(float fadeOutDuration)
{
	if (mCurrentBackGroundMusic != nullptr)
	{
		mCurrentBackGroundMusic->FadeOut(fadeOutDuration, 0.0f);
	}
}

void USoundManager::FadeInBackGroundMusic(float fadeInDuration)
{
	if (mCurrentBackGroundMusic != nullptr)
	{
		mCurrentBackGroundMusic->FadeIn(fadeInDuration, mBackgroundVolume);
	}
}
