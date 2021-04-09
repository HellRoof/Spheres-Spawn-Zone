// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPS_Test_JobGameMode.h"
#include "FPS_Test_JobHUD.h"
#include "FPS_Test_JobCharacter.h"
#include "SphereSpawnZone.h"
#include "UObject/ConstructorHelpers.h"

AFPS_Test_JobGameMode::AFPS_Test_JobGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}

void AFPS_Test_JobGameMode::BeginPlay()
{
	Super::BeginPlay();
}
