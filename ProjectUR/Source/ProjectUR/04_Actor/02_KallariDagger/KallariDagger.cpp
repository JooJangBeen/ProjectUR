// Fill out your copyright notice in the Description page of Project Settings.


#include "KallariDagger.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/MeshComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AKallariDagger::AKallariDagger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComponent);


	

	DaggerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DaggerMesh"));
	DaggerMesh->SetupAttachment(GetRootComponent());
	DaggerMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ProjectileDaggerParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ProjectileDagger"));
	ProjectileDaggerParticle->SetupAttachment(GetRootComponent());
	ProjectileDaggerParticle->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	MovementComp->InitialSpeed = 2500.f;
	MovementComp->MaxSpeed = 2500.f;
	MovementComp->ProjectileGravityScale = 0.5f;
}

// Called when the game starts or when spawned
void AKallariDagger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKallariDagger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

void AKallariDagger::FireInDirection(const FVector& ShootDirection)
{
	MovementComp->Velocity = ShootDirection * MovementComp->InitialSpeed;
}

