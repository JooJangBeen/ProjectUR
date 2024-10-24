// Fill out your copyright notice in the Description page of Project Settings.


#include "CTGameStateBase.h"
#include "../ProjectUR.h"

//게임모드가 StartPlay()를 지시하면 이 게임스테이트에게 명령을 내려서 현재 월드에 있는 모든 액터들에게 BeginPlay()를 호출하고 게임을 시작 하라고 명령을 내림.
//로컬 로직이기때문에 서버에서만 실행이 된다.
void ACTGameStateBase::HandleBeginPlay()
{
	PUR_LOG(LogNetwork, Log, TEXT("% s"), TEXT("Begin"));

	Super::HandleBeginPlay();

	PUR_LOG(LogNetwork, Log, TEXT("% s"), TEXT("End"));
}

//위 HandleBeginPlay와 동일하게 수행이 되는데 bReplicatedHasBegunPlay라는 프로퍼티가 서버로 부터 전송되서 변경이 되서 감지가 되면 함수가 호출이 되고 그때 클라이언트가 신호를 받고 게임을 시작한다.
void ACTGameStateBase::OnRep_ReplicatedHasBegunPlay()
{
	PUR_LOG(LogNetwork, Log, TEXT("% s"), TEXT("Begin"));

	Super::OnRep_ReplicatedHasBegunPlay();

	PUR_LOG(LogNetwork, Log, TEXT("% s"), TEXT("End"));
}
