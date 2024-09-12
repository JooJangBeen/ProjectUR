// Fill out your copyright notice in the Description page of Project Settings.


#include "TeraCharacter.h"


// Sets default values
ATeraCharacter::ATeraCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATeraCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATeraCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATeraCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

