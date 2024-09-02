// Fill out your copyright notice in the Description page of Project Settings.


#include "CTGameModeBase.h"
#include "CTPlayerController.h"

ACTGameModeBase::ACTGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> TestCharacterClassRef(TEXT("/Script/ProjectUR.TestCharacter"));
	
	if (TestCharacterClassRef.Class)
	{
		DefaultPawnClass = TestCharacterClassRef.Class;
	}


	PlayerControllerClass = ACTPlayerController::StaticClass();

}
