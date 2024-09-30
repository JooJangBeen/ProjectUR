// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseCharacter.h"
#include "GrimCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTUR_API AGrimCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AGrimCharacter();

//=====================================================================================
// Default Override Fuction
//=====================================================================================
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;


//=====================================================================================
// Load & Prepare Something
//=====================================================================================
void SetupDefault();
void LoadMeshAnimation();
void LoadEnhancedInput();
void BindInputAction2Fuction(UInputComponent* PlayerInputComponent);
};
