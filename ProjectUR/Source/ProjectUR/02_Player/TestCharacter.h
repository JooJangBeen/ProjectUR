// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "TestCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTUR_API ATestCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	ATestCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;


protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Move(const FInputActionValue& Value) override;
	virtual void Look(const FInputActionValue& Value) override;

	//======================================================================
	// Collision & Raycast
	//======================================================================
protected:
	void PerformRaycastCheck();
	void TestInterAct(const FInputActionValue& Value);

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

};
