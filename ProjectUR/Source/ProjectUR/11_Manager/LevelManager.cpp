// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelManager.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Engine/StreamableManager.h"

ULevelManager::ULevelManager()
{
	
}

void ULevelManager::Initialize(FSubsystemCollectionBase& collection)
{

}

void ULevelManager::BeginLoadingScreen(FName loadingLevelName, FString openLevelPath)
{
	UGameplayStatics::OpenLevel(GetWorld(), loadingLevelName);
	
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

}

void ULevelManager::EndLoadingScreen(FName openLevelPath)
{
	UGameplayStatics::OpenLevel(GetWorld(), openLevelPath);
	
}