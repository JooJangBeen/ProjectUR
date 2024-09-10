// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "../09_Enums/PlayerEnum.h"
#include "CTWorldSettings.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTUR_API ACTWorldSettings : public AWorldSettings
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Selection")
	ECharacterType SelectedCharacter;
};
