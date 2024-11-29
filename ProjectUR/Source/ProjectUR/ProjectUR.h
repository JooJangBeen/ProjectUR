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

/*
* DORM_Never UMETA(DisplayName = "Never")
* DORM_Awake UMETA(DisplayName = "Awake")
* DORM_DormantAll UMETA(DisplayName = "Dormant All"),
* DORM_DormantPartial UMETA(DisplayName = "Dormant Partial"),
* DORM_Initial UMETA(DisplayName = "Initial"),
* 액터의 휴먼 상탱값을 바꿔줄수 있다.
* NetDormancy = DORM_Initial => 해당 액터를 휴면상태로 바꿔준다.
* FlushNetDormancy(); => 함수를 사용하면 휴먼 상태가 해제가 되면서 변경된 속성이 반영이 된다.
* 
* DOREPLIFETIME_CONDITION을 사용해서 해당 컨디션 옵션을 변경이 가능하다.
* 예-> DOREPLIFETIME_CONDITION(ATestServerActor, m_ServerRotationYaw, COND_InitialOnly);
COND_None = 0							UMETA(DisplayName = "None"),							// This property has no condition, and will send anytime it changes 
COND_InitialOnly = 1					UMETA(DisplayName = "Initial Only"),					// This property will only attempt to send on the initial bunch 
COND_OwnerOnly = 2						UMETA(DisplayName = "Owner Only"),						// This property will only send to the actor's owner 
COND_SkipOwner = 3						UMETA(DisplayName = "Skip Owner"),						// This property send to every connection EXCEPT the owner 
COND_SimulatedOnly = 4					UMETA(DisplayName = "Simulated Only"),					// This property will only send to simulated actors/
COND_AutonomousOnly = 5					UMETA(DisplayName = "Autonomous Only"),					// This property will only send to autonomous actors
COND_SimulatedOrPhysics = 6				UMETA(DisplayName = "Simulated Or Physics"),			// This property will send to simulated OR bRepPhysics actors
COND_InitialOrOwner = 7					UMETA(DisplayName = "Initial Or Owner"),				// This property will send on the initial packet, or to the actors owner
COND_Custom = 8							UMETA(DisplayName = "Custom"),							// This property has no particular condition, but wants the ability to toggle on/off via SetCustomIsActiveOverride
COND_ReplayOrOwner = 9					UMETA(DisplayName = "Replay Or Owner"),					// This property will only send to the replay connection, or to the actors owner
COND_ReplayOnly = 10					UMETA(DisplayName = "Replay Only"),						// This property will only send to the replay connection
COND_SimulatedOnlyNoReplay = 11			UMETA(DisplayName = "Simulated Only No Replay"),		// This property will send to actors only, but not to replay connections
COND_SimulatedOrPhysicsNoReplay = 12	UMETA(DisplayName = "Simulated Or Physics No Replay"),	// This property will send to simulated Or bRepPhysics actors, but not to replay connections
COND_SkipReplay = 13					UMETA(DisplayName = "Skip Replay"),						// This property will not send to the replay connection
COND_Dynamic = 14						UMETA(Hidden),											// This property wants to override the condition at runtime. Defaults to always replicate until you override it to a new condition.
COND_Never = 15							UMETA(Hidden),											// This property will never be replicated
COND_NetGroup = 16						UMETA(Hidden),											// This subobject will replicate to connections that are part of the same group the subobject is registered to. Not usable on properties.
COND_Max = 17							UMETA(Hidden)



* RPC 참고 링크 :https://jwatermelon.tistory.com/31
* RPC 종류
* 서버 RPC(Server RPC)
* -서버에서 실행되는 함수이다.
* -클라이언트가 서버에 특정 요청을 보낼 때 사용됨
* -UFUNCTION 매크로를 사용하여 Server로 지정하고, 서버 전용 함수임을 표시
* 예) UFUNCTION(Server, Reliable)
	  void ServerMove(FVector NewLocation);

* 클라이언트 RPC(Client RPC)
* -클라이언트에서 실행되는 함수이다.
* -주로 서버에서 클라이언트로 정보를 보내거나 이벤트를 발생시키기 위해 사용함
* -UFUNCTION 매크로를 Client로 지정하여 클라이언트 전용 함수임을 표시
* 예) UFUNCTION(Client, Reliable)
	  void ClientNotify(FString Message);

* 멀티캐스트 RPC(Multicast RPC)
* -모든 클라이언트에서 호출된다.
* -서버가 이벤트를 발생시켜 네트워크에 연결된 모든 클라이언트가 동일한 정보를 받도록 할 때 유용
* -UFUNCTION 매크로를 NetMulticast로 지정하여 모든 클라이언트에서 실행되도록 설정합니다.
* 예) UFUNCTION(NetMulticast, Reliable)
	  void MulticastOnDeath();

* RPC 매크로 옵션 설명
* Reliable: 네트워크를 통해 반드시 전달되어야 하는 경우에 사용합니다. 중요한 이벤트나 동작일 경우 반드시 사용되며, 네트워크 품질이 나쁘더라도 재전송을 보장함.
* Unreliable: 네트워크 환경에 따라 손실될 수 있지만, 성능 상 이점이 있는 경우에 사용합니다. 예를 들어, 빠른 업데이트가 필요한 경우 일시적으로 패킷 손실이 있어도 상관없는 데이터에 사용함.
* 
* 단일 머신(서버, 클라 RPC)는 앞서서 소유권(오너쉽)을 가지고 있어야 한다. 그래서 기물 오브젝트나 플레이가 아닌경우
* 플레이어 컨트롤러나 폰이랑은 아무런 관계가 없기때문에 오너쉽 자체가 없다. 오너쉽이 없는 오브젝트에 서버 RPC를 쓰면 에러가 뜬다.
* 해결 하기 위해서는 오너쉽을 설정해줘야 하는데 서버에서 주는 액터의 오너를 지정을 해줘야 한다.
* 
* 그냥 GetOwer()를 사용하면 클라이언트의 Ower를 가지고 오기땜문에 서버 코드에 해당 코드를 사용하여 서버에서 준 Ower를 넣어줘야 한다.
* for(FconstPlayerControllerIter Iterator =GetWorld()->GetPlayerControllerIrerator(); Iterator; ++Iterator)
* {
*	APlayerController* PlayerController = Iterator->Get();
*	if(PlayerController && !PlayerController->IsLocalPlayerController())
*	{
*		SetOwner(PlayerController);
*		break;
*	}
* }
* 
* 팁
* #EngineUtils.h 사용하면
* for(APlayerControllerIter playerComtroller : TActorRange<APlayerController>(GetWorld()))
* {
*	if(PlayerController && !PlayerController->IsLocalPlayerController())
*	{
*		SetOwner(PlayerController);
*		break;
*	}
* }
* 이렇게도 사용 가능하다.
* 또 다른 방법으로는 폰의 오너쉡에 대해서 IsLocallyControlled()함수를 사용찾을 수 있다.
* 주의!!-> 생성자 스크립트에서 IsLocallyControlled()함수를 사용 하면 안된다. 생성자 스크립트나 생성자에서는 엔진이 초기화 하는 과정에 호출되기 때문에
* 폰과 컨트롤러 개념 자체도 없는 상황이다.
* 
* 컨트롤러 -> IsLocalController();
* 폰 -> IsLocallyControlled();
* 
* 오너쉽을 확인하는 방법으로는 GetnetConnection()함수를 사용해서 확인 할 수있다.
* 
* !!!RPC를 사용하는 함수에 대해서는 항상 구현부에 _Implementation를 붙혀야한다.!!!
* 왜 _Implementation이 필요한가?
* RPC 함수는 클라이언트와 서버 간 통신을 처리하기 위해 두 가지 역할을 해야 합니다.
* 1.네트워크 호출 처리 (Generated 코드)
*	언리얼 엔진은 선언된 RPC 함수(MulticastRPCTestFunction)의 바디를 자동으로 생성합니다.
*	이 생성된 바디는 내부적으로 네트워크 호출을 수행하고, 적절한 경우 _Implementation을 호출하도록 되어 있습니다.
*	즉, RPC 호출 시 언리얼이 자동 생성한 함수가 실행되고, 네트워크 전송 후 실제 동작을 _Implementation에서 수행합니다.
* 2.로컬 호출 처리 (사용자가 구현)
*	사용자는 _Implementation 접미사가 붙은 함수에 실제 기능을 구현해야 합니다.
*	_Implementation 함수는 네트워크 호출을 통해 전송된 메시지를 수신했을 때 실행됩니다.
* 
* 검증기능
* withValidation : 서버에서 검증 로직을 추가로 구현할 때 추가하는 옵션. 서버 RPC에서만 사용한다. 
* UFUNCTION(NetMulticast, Unreliable, withValidation) 
* 이 키워드를 사용하는경우에는 bool 리턴값으로 함수 뒤에 _validate()를 붙혀줘야 한다.
* 예)
* // _Validate 함수: 유효성 검증
*bool AMyActor::ServerRPCTestFunction_Validate(int32 Value)
*{
*    // Value가 0보다 크면 호출 허용
*    if (Value > 0)
*    {
*        return true;  // 호출 허용
*    }
*    return false;     // 호출 무효화
*}
*void AMyActor::ServerRPCTestFunction_Implementation(int32 Value)
*{
*    UE_LOG(LogTemp, Log, TEXT("서버에서 RPC 호출 처리, 값: %d"), Value);
*}
* 
* ServerRPCTestFunction()라는 함수가 호출이 되었을때 먼저 ServerRPCTestFunction_Validate()를 통해 유효성 검사를 하고,
* 통과가 되었을때만 ServerRPCTestFunction_Implementation()함수가 호출 된다.
*/