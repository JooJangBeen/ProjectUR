// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectURGameMode.h"
#include "ProjectURCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectURGameMode::AProjectURGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
