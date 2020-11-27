// Copyright Epic Games, Inc. All Rights Reserved.

#include "Unreal_Assignment3GameMode.h"
#include "Unreal_Assignment3PlayerController.h"
#include "Unreal_Assignment3Character.h"
#include "UObject/ConstructorHelpers.h"

AUnreal_Assignment3GameMode::AUnreal_Assignment3GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AUnreal_Assignment3PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}