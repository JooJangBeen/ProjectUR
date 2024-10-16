// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ProcedualSpider.generated.h"

UCLASS()
class PROJECTUR_API AProcedualSpider : public ACharacter
{
	GENERATED_BODY()

public:
	AProcedualSpider();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	float MoveSpeed;
};
