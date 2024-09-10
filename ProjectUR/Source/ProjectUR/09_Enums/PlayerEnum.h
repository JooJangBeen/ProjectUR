// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerEnum.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	Kallari UMETA(DisplayName = "Kallari"),
	Terra UMETA(DisplayName = "Terra"),
	Grim UMETA(DisplayName = "GRIM.exe"),
	Narbash UMETA(DisplayName = "Narbash")
};

