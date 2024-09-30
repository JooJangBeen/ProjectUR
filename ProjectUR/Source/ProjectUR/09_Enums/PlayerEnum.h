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
	Grim UMETA(DisplayName = "GRIM.exe"),
	Narbash UMETA(DisplayName = "Narbash"),
	Terra UMETA(DisplayName = "Terra")
};


#define PLAYERDEFAULTCAMLENTH 250.f
#define PLAYERDEFAULTCAMPOS FVector(0.f,90.f,90.f)
