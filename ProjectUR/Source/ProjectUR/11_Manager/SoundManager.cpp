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

void USoundManager::PlayBackGroundMusic(USoundBase* music, float fadeinDuration)
{
	if (music == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("is NullPtr BackGroundMusicCue"));
		return;
	}

	if (mCurrentBackGroundMusic != NULL)
	{
		mCurrentBackGroundMusic->FadeOut(fadeinDuration, 0.0f);
	}

	mCurrentBackGroundMusic = UGameplayStatics::SpawnSound2D(this, music, mBackgroundVolume);

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

void USoundManager::PlaySFX(USoundBase* sfxMusic, AActor* actor)
{
	if (sfxMusic == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("is NullPtr sfxMusic"));
		return;
	}

	UAudioComponent* audioComponent = nullptr;


	if (!mSfxSoundMap.Contains(sfxMusic))
	{
		//UAudioComponent* AudioComponent = UGameplayStatics::SpawnSoundAttached(
		//	SoundCue,                       // 재생할 사운드
		//	Actor->GetRootComponent(),       // 부착할 컴포넌트 (여기서는 액터의 루트 컴포넌트)
		//	NAME_None,                       // 부착할 소켓 이름 (필요 없을 경우 NAME_None)
		//	FVector::ZeroVector,             // 상대적인 위치 오프셋
		//	FRotator::ZeroRotator,           // 상대적인 회전 오프셋
		//	EAttachLocation::KeepRelativeOffset, // 상대적 위치를 유지
		//	true,                            // 액터가 파괴되면 사운드도 정지
		//	1.0f,                            // 볼륨 설정
		//	1.0f,                            // 피치 설정(재생속도)
		//	0.0f,                            // 시작 시간
		//	nullptr,                         // 감쇠 설정 (없으면 기본값 사용) 선택: 사운드 감쇠(Attenuation) 설정을 지정합니다. 감쇠 설정은 사운드가 거리에 따라 볼륨이 줄어드는 방식 등을 제어합니다.
		//										지정하지 않으면 프로젝트의 기본 감쇠 설정을 사용합니다.
		//	nullptr,                         // 동시성 설정 (없으면 기본값 사용) 선택: 사운드 동시성(Concurrency) 설정을 지정합니다. 동시성 설정은 동일한 사운드가 얼마나 많은 인스턴스까지 동시에 재생될 수 있는지 제어합니다.
		//	true                             // 재생이 끝난 후 자동 파괴
		//);
		audioComponent = UGameplayStatics::SpawnSoundAttached(sfxMusic, actor->GetRootComponent(), NAME_None, actor->GetActorLocation(),
			EAttachLocation::KeepRelativeOffset, true, mSfxVolume, 1.0f, 0.0f, nullptr, nullptr, false);// 삭제를 안하므로 직접 삭제 해야한다.

		mSfxSoundMap.Add(sfxMusic, audioComponent);
	}
	else
	{
		mSfxSoundMap[sfxMusic]->Play();
	}
}


void USoundManager::PlayUISound(USoundBase* uiSound)
{
	if (uiSound == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("is NullPtr uiSound"));
		return;
	}

	UAudioComponent* audioComponent = nullptr;

	if (!mUiSoundMap.Contains(uiSound))
	{
		//UAudioComponent* AudioComponent = UGameplayStatics::SpawnSound2D(
		//	this,                // WorldContextObject (보통 this 또는 GetWorld() 사용)
		//	SoundCue,            // 재생할 사운드
		//	1.0f,                // 볼륨
		//	1.0f,                // 피치
		//	0.0f,                // 시작 시간
		//	nullptr,             // 동시성 설정 (기본값 사용)
		//	false,               // 레벨 전환 시 사운드 유지 여부
		//	true                 // 재생 후 자동 파괴 여부
		//);
		audioComponent = UGameplayStatics::SpawnSound2D(GetWorld(), uiSound, mUiVolume, 1.0f, 0.0f, nullptr, false, false);

		mUiSoundMap.Add(uiSound, audioComponent);
	}
	else
	{
		mUiSoundMap[uiSound]->Play();
	}
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

void USoundManager::RemoveSFXSound(USoundBase* sfxSoundBase)
{
	if (!mSfxSoundMap.Contains(sfxSoundBase)) return;

	mSfxSoundMap[sfxSoundBase]->DestroyComponent();
	mSfxSoundMap.Remove(sfxSoundBase);
}

void USoundManager::RemoveUISound(USoundBase* uiSoundBase)
{
	if (!mUiSoundMap.Contains(uiSoundBase)) return;

	mUiSoundMap[uiSoundBase]->DestroyComponent();
	mUiSoundMap.Remove(uiSoundBase);
}
