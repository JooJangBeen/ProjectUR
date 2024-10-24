// Fill out your copyright notice in the Description page of Project Settings.


#include "CTGameModeBase.h"
#include "CTPlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "CTWorldSettings.h"
#include "EnhancedInputSubsystems.h"
#include "../ProjectUR.h"
#include "CTGameStateBase.h"

ACTGameModeBase::ACTGameModeBase()
{


	ACTWorldSettings* WorldSettings = Cast<ACTWorldSettings>(GetWorldSettings());
	if (WorldSettings)
	{
		switch (WorldSettings->SelectedCharacter)
		{
		case ECharacterType::Kallari:
		{
			static ConstructorHelpers::FClassFinder<APawn> CharacterClassRef(TEXT("/Script/ProjectUR.KallariCharacter"));
			if (CharacterClassRef.Class)
				DefaultPawnClass = CharacterClassRef.Class;
		}
			break;
		case ECharacterType::Grim:
		{
			static ConstructorHelpers::FClassFinder<APawn> CharacterClassRef(TEXT("/Game/02_Player/02_Grim/BP_Grim.BP_Grim_C"));
			if (CharacterClassRef.Class)
				DefaultPawnClass = CharacterClassRef.Class;
		}
			break;
		case ECharacterType::Narbash:
		{
			static ConstructorHelpers::FClassFinder<APawn> CharacterClassRef(TEXT("/Game/02_Player/04_PCNarbash/BP_PCNarbash.BP_PCNarbash_C"));
			if (CharacterClassRef.Class)
				DefaultPawnClass = CharacterClassRef.Class;
		}
			break;
		case ECharacterType::Terra:
		{
			static ConstructorHelpers::FClassFinder<APawn> CharacterClassRef(TEXT("/Script/ProjectUR.TeraCharacter"));
			if (CharacterClassRef.Class)
				DefaultPawnClass = CharacterClassRef.Class;
		}
			break;

		default:
			break;
		}
	}


	PlayerControllerClass = ACTPlayerController::StaticClass();
	GameStateClass = ACTGameStateBase::StaticClass();
}

void ACTGameModeBase::BeginPlay()
{
	Super::BeginPlay();

}

//클라이언트의 접속요청을 처리하는 함수
void ACTGameModeBase::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	PUR_LOG(LogNetwork, Log, TEXT("% s"), TEXT("======================================================"));
	PUR_LOG(LogNetwork, Log, TEXT("% s"), TEXT("Begin"));

	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);

	PUR_LOG(LogNetwork, Log, TEXT("% s"), TEXT("End"));
}

//접속을 허용한 클라이언트에 대응하는 플레이컨트롤러를 만드는 함수
APlayerController* ACTGameModeBase::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	PUR_LOG(LogNetwork, Log, TEXT("% s"), TEXT("Begin"));

	APlayerController* NewPlayerController = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
	
	PUR_LOG(LogNetwork, Log, TEXT("% s"), TEXT("End"));
	return NewPlayerController;
}

//플레이어 입장을 위해 플레이어에 필요한 기본 설정을 모두 마무리하는 함수
void ACTGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	PUR_LOG(LogNetwork, Log, TEXT("% s"), TEXT("Begin"));

	Super::PostLogin(NewPlayer);
	UNetDriver* NetDriver = GetNetDriver();
	if (NetDriver)
	{
		if (NetDriver->ClientConnections.Num() == 0)
		{
			PUR_LOG(LogNetwork, Log, TEXT("%s"), TEXT("No Client Connection"));
		}
		else
		{
			for (const auto& Connection : NetDriver->ClientConnections)
			{
				PUR_LOG(LogNetwork, Log, TEXT("Client Connentions: %s"), *Connection->GetName());
			}
		}
	}
	else
	{
		PUR_LOG(LogNetwork, Log, TEXT("%s"), TEXT("No NetDriver"));
	}
	
	PUR_LOG(LogNetwork, Log, TEXT("% s"), TEXT("End"));
}

//게임의 시작을 지시하는 함수
void ACTGameModeBase::StartPlay()
{
	PUR_LOG(LogNetwork, Log, TEXT("% s"), TEXT("Begin"));

	Super::StartPlay();

	PUR_LOG(LogNetwork, Log, TEXT("% s"), TEXT("End"));
}



