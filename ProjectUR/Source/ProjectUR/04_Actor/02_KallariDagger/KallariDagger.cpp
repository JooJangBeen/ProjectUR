// Fill out your copyright notice in the Description page of Project Settings.


#include "KallariDagger.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/MeshComponent.h"
#include "Components/SphereComponent.h"
#include "../02_Player/BaseCharacter.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AKallariDagger::AKallariDagger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = CollisionComponent;
	CollisionComponent->InitSphereRadius(20.f);

	// 콜리전 이벤트를 활성화
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//CollisionComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic")); // 오버랩을 감지하도록 설정
	CollisionComponent->SetCollisionObjectType(ECC_WorldDynamic);
	//CollisionComponent->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	CollisionComponent->SetGenerateOverlapEvents(true);

	// Overlap 이벤트 바인딩
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AKallariDagger::EclipseDagger_OverlapBegin);
	

	DaggerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DaggerMesh"));
	DaggerMesh->SetupAttachment(GetRootComponent());
	DaggerMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ProjectileDaggerParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ProjectileDagger"));
	ProjectileDaggerParticle->SetupAttachment(GetRootComponent());
	ProjectileDaggerParticle->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	MovementComp->InitialSpeed = 1500.f;
	MovementComp->MaxSpeed = 1500.f;
	MovementComp->ProjectileGravityScale = 1.f;


	DaggerMesh->SetVisibility(false);  // Mesh는 숨김
	ProjectileDaggerParticle->SetVisibility(true);  // 파티클은 보임

	bIsOnGround = false;
}

// Called when the game starts or when spawned
void AKallariDagger::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(3.5f);

	
}

// Called every frame
void AKallariDagger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AKallariDagger::EclipseDagger_OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ABaseCharacter::StaticClass()))
		return;

	if (OtherActor && OtherComp)
	{


		if (OtherComp->GetCollisionObjectType() == ECC_WorldStatic)
		{

			bIsOnGround = true;

			SetLifeSpan(12.f);
			MovementComp->StopMovementImmediately();
			MovementComp->ProjectileGravityScale = 0.f;

			DaggerMesh->SetVisibility(true);
			ProjectileDaggerParticle->SetVisibility(false);



			float RandomXRotation = FMath::RandRange(-70.0f, 70.0f);
			FRotator NewRotation = DaggerMesh->GetComponentRotation();
			NewRotation.Roll = RandomXRotation;
			DaggerMesh->SetWorldRotation(NewRotation);

		}
	}
}

void AKallariDagger::FireInDirection(const FVector& ShootDirection)
{
	MovementComp->Velocity = ShootDirection * MovementComp->InitialSpeed;
}



