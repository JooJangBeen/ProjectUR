// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InputActionValue.h"
#include "../09_Enums/PlayerEnum.h"
#include "CTGameModeBase.generated.h"

/**
 * 
 */


UCLASS()
class PROJECTUR_API ACTGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACTGameModeBase();

public:
	virtual void BeginPlay() override;
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void StartPlay() override;
};
