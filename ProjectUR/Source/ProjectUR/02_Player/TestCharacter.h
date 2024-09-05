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
	void TestInterAct(const FInputActionValue& Value);

	//======================================================================
	// Collision & Raycast
	//======================================================================
protected:
	UFUNCTION()
	void TestCharacterOnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,	bool bFromSweep, const FHitResult& SweepResult);
	void TestCharacterOnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,UPrimitiveComponent* OtherComp, FVector NormalImpulse,	const FHitResult& Hit);


	void PerformRaycastCheck();
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

};
