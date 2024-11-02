// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcedualSpider.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AProcedualSpider::AProcedualSpider()
{
	PrimaryActorTick.bCanEverTick = true;


	GetCapsuleComponent()->DestroyComponent();  // 캡슐 콜리전 제거
	UBoxComponent* BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxCollision->SetBoxExtent(FVector(70.f, 70.f, 100.f));
	BoxCollision->SetRelativeLocation(FVector(0.0f, 0.f, 100.f));
	BoxCollision->SetCollisionProfileName(TEXT("Pawn"));
	RootComponent = BoxCollision;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/03_Monster/97_ProcedualMonster/Spider/Mesh/SK_Spider.SK_Spider'"));
	if (CharacterMeshRef.Object)
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstClassRef(TEXT("/Game/03_Monster/97_ProcedualMonster/Spider/ABP_PDSpider.ABP_PDSpider_C"));
	if (AnimInstClassRef.Class)
		GetMesh()->SetAnimInstanceClass(AnimInstClassRef.Class);

	GetMesh()->SetupAttachment(RootComponent);
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0, -100.0f));

	FRotator NewRotation = GetMesh()->GetComponentRotation();
	NewRotation.Yaw -= 90.0f;
	GetMesh()->SetWorldRotation(NewRotation);


	//GetArrowComponent()->SetupAttachment(RootComponent);

	MoveSpeed = 20.f;

}

// Called when the game starts or when spawned
void AProcedualSpider::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProcedualSpider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	MoveSpeed = 100.f;

	SetActorLocation(GetActorLocation() + (GetActorForwardVector() * MoveSpeed * DeltaTime));
}

// Called to bind functionality to input
void AProcedualSpider::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

