// Fill out your copyright notice in the Description page of Project Settings.


#include "CTGameModeBase.h"
#include "CTPlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "CTWorldSettings.h"
#include "EnhancedInputSubsystems.h"

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
			static ConstructorHelpers::FClassFinder<APawn> CharacterClassRef(TEXT("/Script/ProjectUR.TestCharacter"));
			if (CharacterClassRef.Class)
				DefaultPawnClass = CharacterClassRef.Class;
		}
			break;
		case ECharacterType::Narbash:
		{
			static ConstructorHelpers::FClassFinder<APawn> CharacterClassRef(TEXT("/Script/ProjectUR.KallariCharacter"));
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


}

void ACTGameModeBase::BeginPlay()
{


}



