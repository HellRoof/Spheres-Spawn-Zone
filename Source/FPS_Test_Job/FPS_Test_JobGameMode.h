// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPS_Test_JobGameMode.generated.h"

UCLASS(minimalapi)
class AFPS_Test_JobGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFPS_Test_JobGameMode();

	virtual void BeginPlay() override;
};



