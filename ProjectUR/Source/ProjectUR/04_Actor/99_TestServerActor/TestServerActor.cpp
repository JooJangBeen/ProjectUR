// Fill out your copyright notice in the Description page of Project Settings.


#include "TestServerActor.h"
#include "Components/StaticMeshComponent.h"
#include "Net/UnrealNetwork.h"
#include "../ProjectUR.h"


// Sets default values
ATestServerActor::ATestServerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_ServerRotationYaw = 0.0f;
	m_RotationRate = 30.0f;

	bReplicates = true;
	NetUpdateFrequency = 1.0f;//액터리플리케이션의 빈도(1~100) 기본값은 100이다.
}

// Called when the game starts or when spawned
void ATestServerActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestServerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())//서버일때
	{
		AddActorLocalRotation(FRotator(0.0f, m_RotationRate * DeltaTime, 0.0f));
		m_ServerRotationYaw = RootComponent->GetComponentRotation().Yaw;
	}
	else
	{
		//FRotator NewRotator = RootComponent->GetComponentRotation();
		//NewRotator.Yaw = m_ServerRotationYaw;
		//RootComponent->SetWorldRotation(NewRotator);

		m_ClientTimeSinceUpdate += DeltaTime;
		if (m_ClientTimeBetweenLastUpdate < KINDA_SMALL_NUMBER)
		{
			return;
		}

		//보간
		const float EstimateRotationYaw = m_ServerRotationYaw + m_RotationRate * m_ClientTimeBetweenLastUpdate;
		const float LerpRatio = m_ClientTimeSinceUpdate / m_ClientTimeBetweenLastUpdate;

		FRotator ClientRotator = RootComponent->GetComponentRotation();
		const float ClientNewYaw = FMath::Lerp(m_ServerRotationYaw, EstimateRotationYaw, LerpRatio);
		ClientRotator.Yaw = ClientNewYaw;
		RootComponent->SetWorldRotation(ClientRotator);
	}

}

void ATestServerActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATestServerActor, m_ServerRotationYaw);// 복제할 변수를 등록
}

//FInBunch: 데이터, UNetConnection: 채널을 관리하는 담당자 
//클라이언트에서만 호출이 된다(서버와의 포탈이 열렸다)
void ATestServerActor::OnActorChannelOpen(FInBunch& InBunch, UNetConnection* Connection)
{
	PUR_LOG(LogNetwork, Log, TEXT("%s"), TEXT("Begin"));

	Super::OnActorChannelOpen(InBunch, Connection);

	PUR_LOG(LogNetwork, Log, TEXT("%s"), TEXT("End"));
}

void ATestServerActor::OnRep_ServerRotationYaw()
{
	FRotator NewRotator = RootComponent->GetComponentRotation();
	NewRotator.Yaw = m_ServerRotationYaw;
	RootComponent->SetWorldRotation(NewRotator);
	
	m_ClientTimeBetweenLastUpdate = m_ClientTimeSinceUpdate;
	m_ClientTimeSinceUpdate = 0.0f;
}

