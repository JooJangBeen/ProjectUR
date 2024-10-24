// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#define LOG_LOCALROLEINFO *(UEnum::GetValueAsString(TEXT("Engine.ENetRole"), GetLocalRole()))
#define LOG_REMOTEROLEINFO *(UEnum::GetValueAsString(TEXT("Engine.ENetRole"), GetRemoteRole()))
#define LOG_NETMODEINFO ((GetNetMode() == ENetMode::NM_Client) ? *FString::Printf(TEXT("Client%d"), static_cast<int32>(GPlayInEditorID)) : ((GetNetMode() == ENetMode::NM_Standalone) ? TEXT("STANDALONE") : TEXT("SERVER")))
#define LOG_CALLINFO ANSI_TO_TCHAR(__FUNCTION__)	
// ...가변인자를 받는것이다. 로그 매크로 선언
#define PUR_LOG(LogCat, Verbosity, Format, ...)  UE_LOG(LogCat, Verbosity, TEXT("[%s][%s/%s] %s %s"), LOG_NETMODEINFO, LOG_LOCALROLEINFO, LOG_REMOTEROLEINFO, LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

DECLARE_LOG_CATEGORY_EXTERN(LogNetwork, Log, All);//네트워크 로그 카테고리 지정

/*
* None : 액터가 존재하지 않음
* Authority : 서비스를 대표하는 신뢰할수있는 역할. 게임 로직을 수행한다.
* AutonomousProxy : Authority를 가진 오브젝트의 복제품. 일부 게임 로직을 수행한다.(예: 플레이어 컨트롤러)
* SimulatedProxy : Authority를 가진 오브젝트의 복제품. 게임로직을 수행하지 않는다.
*/

/*
* 커넥션 핸드셰이킹: 네트웍으로 접속하는 두 컴퓨터가 잘 연결되었는지 확인하는 과정
*/

/*
* 액터 리플리케이션 : 특정 플레이어에 속한 액터의 정보를 네트웍 내 다른 플레이어에게 복제하는 작업
* 리플리케이션의 방법은 크게 두가지가 있는데 프로퍼티 리플리케이션, RPC(Remote Procedure call) 있다.
* 
* 기본 액터의 로딩 :클라이언트가 초기화 될때 모든 액터의 정보를 서버로부터 받는것은 비효율적이다.
* 따라서 기본 배경의 관련된 액터는 맵을 통해 스스로 로딩하도록 설계되어 있다.
* 고정으로 제공하는 액터의 예 : 레벨을 구성하는 배경 액터
* 동적으로 생성하는 액터의 예 : 플레이어 컨르롤러와 폰
* 고정 액터와 동적 액터를 구분 하기위해서 NetLoadOnClient 속성을 제공하고있다.(각 액터의 디테일에 속성값이 있음) 참이면 서버와 통신 없이 클라에서 로딩한다.
*/

/* 리플리케이션 프로퍼티(속성)의 지정
* 액터의 리플리케이션 속성을 참으로 지정한다.(bReplicates속성을 참으로 지정함)
* 네트웍으로 복제할 액터의 속성을 키워드로 지정(UPROPERTY에 Relicated 키워드 설정)
* GetLifeTimeReplicatedProps 함수에 네트웍으로 복제할 속성을 추가(#include "Net/UnrealNetwork.h"헤더 파일 지정)
*  ->(DOREPLIFETIME 매크로를 사용해 복제할 속성을 명시) 
*/

/*
* 언리얼 인사이트
* 언리얼 프로그램의 다양한 퍼포먼스를 체크할수있는 강력한 프로파일링 도구
* 프로그램 프로파일링뿐만 아니라 네트웍 상태도 확인 할수 있음
* 
* 언리얼 인사이트 구동을 위한 환경 설정
* ->언리얼엔진의 설치 폴더 확인
* ->인사이트프로그램의 숏컷 생성
* ->언리얼에디터 실행파일의 PATH설정
* ->언리얼 에디터를 구동하기 위한 배치파일 제작
*/