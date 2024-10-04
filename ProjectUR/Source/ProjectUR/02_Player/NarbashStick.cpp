// Fill out your copyright notice in the Description page of Project Settings.


#include "NarbashStick.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/MeshComponent.h"
#include "CableComponent.h"

// Sets default values
ANarbashStick::ANarbashStick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODYMESH"));
	BodyMesh->SetupAttachment(RootComp);
	BodyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CableComp = CreateDefaultSubobject<UCableComponent>(TEXT("CABLECOMP"));
	CableComp->SetupAttachment(RootComp);
	CableComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("PROJECTILEMOVEMENT"));
	MovementComp->InitialSpeed = 1600.f;
	MovementComp->MaxSpeed = 1600.f;
	MovementComp->ProjectileGravityScale = 0.f;

}

// Called when the game starts or when spawned
void ANarbashStick::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANarbashStick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	BodyMesh->AddRelativeRotation(FRotator(0.f, 0.f, 20.f));

}

void ANarbashStick::AttachCableEnd(USkeletalMeshComponent* AttachMesh, FName AttachSocketName)
{
	CableComp->SetAttachEndToComponent(AttachMesh, AttachSocketName);
}

