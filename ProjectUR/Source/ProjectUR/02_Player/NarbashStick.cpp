// Fill out your copyright notice in the Description page of Project Settings.


#include "NarbashStick.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/MeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "CableComponent.h"

// Sets default values
ANarbashStick::ANarbashStick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootComp = CreateDefaultSubobject<USphereComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);
	RootComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODYMESH"));
	BodyMesh->SetupAttachment(RootComp);
	BodyMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	BodyMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	BodyMesh->OnComponentBeginOverlap.AddDynamic(this, &ANarbashStick::StickOnOvelapBegin);
	BodyMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BodyMesh->SetGenerateOverlapEvents(true);
	BodyMesh->SetSimulatePhysics(false);

	CableComp = CreateDefaultSubobject<UCableComponent>(TEXT("CABLECOMP"));
	CableComp->SetupAttachment(BodyMesh);
	CableComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("PROJECTILEMOVEMENT"));
	MovementComp->InitialSpeed = 1600.f;
	MovementComp->MaxSpeed = 1600.f;
	MovementComp->ProjectileGravityScale = 0.f;
	MovementComp->Velocity = GetActorForwardVector() * MovementComp->InitialSpeed;

	IsHitLandform = false;

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

	if(!IsHitLandform)
		BodyMesh->AddRelativeRotation(FRotator(0.f, 0.f, 20.f));

}

void ANarbashStick::AttachCableEnd(USkeletalMeshComponent* AttachMesh, FName AttachSocketName)
{
	CableComp->SetAttachEndToComponent(AttachMesh, AttachSocketName);
}

void ANarbashStick::StickOnOvelapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		BodyMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
		BodyMesh->SetGenerateOverlapEvents(false);
		BodyMesh->SetSimulatePhysics(true);
		BodyMesh->SetAllMassScale(80.f);
		//BodyMesh->SetLinearDamping(1.0f);
		//BodyMesh->SetAngularDamping(1.0f);

		IsHitLandform = true;
	}

}
