// Fil//l out your copyright notice in the Description page of Project Settings.


#include "LevelManager.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Engine/StreamableManager.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Engine/AssetManager.h"

ULevelManager::ULevelManager()
{
	
}

void ULevelManager::Initialize(FSubsystemCollectionBase& collection)
{

}

void ULevelManager::BeginLoadingScreen(FName loadingLevelName, FString openLevelPath)
{
	UGameplayStatics::OpenLevel(GetWorld(), loadingLevelName);
	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
	TSharedPtr<FStreamableHandle> Handle = StreamableManager.RequestAsyncLoad(openLevelPath, FStreamableDelegate::CreateLambda([&, this]() {
		UGameplayStatics::OpenLevel(GetWorld(), FName(openLevelPath));
	}));

	/*
	UGameplayStatics::OpenLevel(GetWorld(), loadingLevelName);
	ULevelStreamingDynamic::FLoadLevelInstanceParams pp(GetWorld(), openLevelPath, FTransform());
	bool a = true;
	ULevelStreamingDynamic* StreamingLevel = ULevelStreamingDynamic::LoadLevelInstance(pp, a);

	if (StreamingLevel)
	{
		StreamingLevel->OnLevelLoaded.AddDynamic(this, &ULevelManager::EndLoading);

		//StreamingLevel->OnLevelLoaded.AddDynamic(this, &ULevelManager::EndLoadingScreen);
	}
	//==================================================================================//
	LoadPackageAsync(openLevelPath, FLoadPackageAsyncDelegate::CreateLambda([&, this](const FName& PackagaName, UPackage* loadedPackage, EAsyncLoadingResult::Type Result)
		{
			if (Result == EAsyncLoadingResult::Succeeded)
			{
				EndLoadingScreen(PackagaName);
			}
		}
	),
	0,
	PKG_ContainsMap);
	*/
}

void ULevelManager::EndLoadingScreen(FName openLevelPath)
{
	UGameplayStatics::OpenLevel(GetWorld(), openLevelPath);
	
}

void ULevelManager::EndLoading()
{
	UGameplayStatics::OpenLevel(GetWorld(), "PreviewSceneIndoor");

}