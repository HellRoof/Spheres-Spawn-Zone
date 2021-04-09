// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Target.h"
#include "Components/SphereComponent.h"
#include "SphereSpawnZone.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnScoreChanged);

UCLASS()
class FPS_TEST_JOB_API ASphereSpawnZone : public AActor
{
	GENERATED_BODY()

public:

	ASphereSpawnZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Sphere collision component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USphereComponent* CollisionComp;
	
	FRandomStream rand;

	//Waves Setting
	UPROPERTY(EditAnywhere, Category = "Wave Setting")
		float SpawnZoneRadiusToFirstWave{2000.f};

	UPROPERTY(EditAnywhere, Category = "Wave Setting")
		float SpawnZoneRadiusToNextWaves{1500.f};
	
	UPROPERTY(EditAnywhere, Category = "Wave Setting")
		int copyOfSphere{ 15 };

	UPROPERTY(EditAnywhere, Category = "Wave Setting")
		TSubclassOf<ATarget> SphereClass;
	
	UPROPERTY(EditAnywhere, Category = "Wave Setting")
		float SpawnZoneScaleInPercent{1.05f};

	UPROPERTY(EditAnywhere, Category = "Wave Setting")
		int ScaleCountOfSphereInPercent{10};

	UPROPERTY(EditAnywhere, Category = "Wave Setting")
		float CountDeathSphereToNextWave{ 10 };

	UPROPERTY(EditAnywhere, Category = "Wave Setting")
		float ScaleCountDeathSphereToNextWaveInPercent{ 1.f };

	UPROPERTY(EditAnywhere, Category = "Wave Setting")
		float DistanceBetweenSphereTarget{80.f};

	//Game score
	UPROPERTY(BlueprintReadOnly)
		int32 Score{0}; 

	//Score delegate
	UPROPERTY(BlueprintAssignable)
		FOnScoreChanged OnScoreChange;
	
	//Count of death sphere per one wave
	int CountOfDeadSphere{ 0 };

	//SpawnZone Radius
	float SphereRadius{SpawnZoneRadiusToFirstWave};

	//Map of all ATarget on level and their name
	TMap<int32, ATarget*> HandlerATargetLocation;

	
public:

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }

	UFUNCTION()
	void SphereSpawn(); 

	//Delegate function
	UFUNCTION()
	void OnSphereDestroyed(int32 TargetID);

	//Teleport SpawnZone to player
	void TeleportToPlayer();

	//Update count of sphere to after wave
	void UpdateCountOfSphere();

	//Add count of sphere need to go to next wave
	void AddCountSphereNeedToNextWave();

	//Update sphere radius after wave
	void UpdateSpawnZoneRadius();

	//Create new seed for a better random
	void GenerateNewRandSeed();

	//Get Distance between center of SpawnZone and SphereRadius_MAXVALUE
	float GetRandDistanceForSpherePlace();

	FVector FindPlaceForNextSphere();

	void CalculateScore();
};
