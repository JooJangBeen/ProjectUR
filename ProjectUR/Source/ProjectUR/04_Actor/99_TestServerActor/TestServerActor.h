// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestServerActor.generated.h"

UCLASS()
class PROJECTUR_API ATestServerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestServerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	//
	virtual void OnActorChannelOpen(class FInBunch& InBunch, class UNetConnection* Connection) override;
	//Replicated 키워드를 붙여줘야지만 자동으로 언리얼엔진의 네트워크 기능을 사용해서 다른클라이언트로 복제가 된다.
	//UPROPERTY(Replicated)
	// 
	//함수를 선언 하는경우 서버에서 값이 바뀔때 호출을 한다.(클라에서만 호출 해당 함수에 UFUNCTION()을 붙혀 줘야한다.)
	//UPROPERTY(ReplicatedUsing = OnRep_ServerRotationYaw)
	UPROPERTY(ReplicatedUsing = OnRep_ServerRotationYaw)
	float m_ServerRotationYaw;
	float m_RotationRate = 30.0f;
	float m_ClientTimeSinceUpdate = 0.0f;//서버로부터 패킷을 받고 이후 얼마정도 시간이 경과 되었는지
	float m_ClientTimeBetweenLastUpdate = 0.0f;//데이터를 받고 다음 데이터를 받을때까지의  시간

	UFUNCTION()
	void OnRep_ServerRotationYaw();


};
