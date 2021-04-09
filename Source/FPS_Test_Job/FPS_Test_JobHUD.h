// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FPS_Test_JobHUD.generated.h"

UCLASS()
class AFPS_Test_JobHUD : public AHUD
{
	GENERATED_BODY()

public:
	AFPS_Test_JobHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

