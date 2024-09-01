// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Engine/StreamableManager.h"
#include "LevelManager.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECTUR_API ULevelManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	ULevelManager();

public:
	virtual void Initialize(FSubsystemCollectionBase& collection);

	UFUNCTION(BlueprintCallable)
	virtual void BeginLoadingScreen(FName loadingLevelName, FString openLevelPath);

	UFUNCTION()
	virtual void EndLoadingScreen(FName openLevelPath);

};
