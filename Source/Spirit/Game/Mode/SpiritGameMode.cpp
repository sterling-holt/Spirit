// Copyright Epic Games, Inc. All Rights Reserved.

#include "SpiritGameMode.h"
#include "Spirit/Character/SpiritCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASpiritGameMode::ASpiritGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}