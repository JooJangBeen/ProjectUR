// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TextRenderActor.h"
#include "NetworkTextRenderActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTUR_API ANetworkTextRenderActor : public ATextRenderActor
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	FString GetNetMode();
};
