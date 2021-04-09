#include "SphereSpawnZone.h"
#include "Math/UnrealMathUtility.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASphereSpawnZone::ASphereSpawnZone()
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(SphereRadius);

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ASphereSpawnZone::BeginPlay()
{
	Super::BeginPlay();

	/*TeleportToPlayer();*/

	SphereSpawn();

	SphereRadius = SpawnZoneRadiusToNextWaves;
	CollisionComp->SetSphereRadius(SphereRadius);

	GenerateNewRandSeed();

}

void ASphereSpawnZone::SphereSpawn()
{
	GenerateNewRandSeed();
	
	for (int i{ 1 }; i <= copyOfSphere; ++i)
	{
		AActor* SpawnedSphere{nullptr};
		FVector RandVector;
		
		if (HandlerATargetLocation.Num() > 0)
		{
			RandVector = FindPlaceForNextSphere();
		}
		else 
			if(HandlerATargetLocation.Num() == 0)
		{
			RandVector = GetActorLocation() + rand.GetUnitVector() * GetRandDistanceForSpherePlace();
		
			if (RandVector.Z < 0)
			{
			RandVector.Z *= -1;
			}
		}
		
		SpawnedSphere = GetWorld()->SpawnActor(SphereClass, &RandVector/*, 0, SpawnParams*/);
		if (ATarget* Sphere = Cast<ATarget>(SpawnedSphere))
		{	
			Sphere->OnSphereDestroyed.AddDynamic(this, &ASphereSpawnZone::OnSphereDestroyed);
			HandlerATargetLocation.Add(Sphere->GetUniqueID(), Sphere);
		}
	}
	UpdateCountOfSphere();
}

void ASphereSpawnZone::OnSphereDestroyed(int32 TargetID)
{
	CalculateScore();
	
	HandlerATargetLocation.Remove(TargetID);
	
	++CountOfDeadSphere;
	if (CountOfDeadSphere >= CountDeathSphereToNextWave)
	{
		CountOfDeadSphere = 0;

		//Update SpawnZone radius
		UpdateSpawnZoneRadius();

		//Update count of Sphere need to next wave
	    AddCountSphereNeedToNextWave();

		//Teleport spawn zone to playe after wave
		TeleportToPlayer();

		//Spawn target sphere for next wave
		SphereSpawn();
	}
}

void ASphereSpawnZone::TeleportToPlayer()
{
	if (APlayerController* FirstPlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (APawn* PlayerPawn = FirstPlayerController->GetPawn())
		{
			
			FVector PlayerLocation = PlayerPawn->GetActorLocation();
			
			SetActorLocation(PlayerLocation);
			
		}
	}
}

void ASphereSpawnZone::UpdateCountOfSphere()
{
	copyOfSphere += (static_cast<float>(copyOfSphere) / 100.f) * ScaleCountOfSphereInPercent;
}

void ASphereSpawnZone::AddCountSphereNeedToNextWave()
{
	CountDeathSphereToNextWave += (CountDeathSphereToNextWave / 100.f) * ScaleCountDeathSphereToNextWaveInPercent;
}

void ASphereSpawnZone::UpdateSpawnZoneRadius()
{
	SpawnZoneRadiusToNextWaves += (SpawnZoneRadiusToNextWaves / 100.f) * SpawnZoneScaleInPercent;

	SphereRadius = SpawnZoneRadiusToNextWaves;
	CollisionComp->SetSphereRadius(SphereRadius, false);
}

void ASphereSpawnZone::GenerateNewRandSeed()
{
	rand.GenerateNewSeed();
}

float ASphereSpawnZone::GetRandDistanceForSpherePlace()
{
	return FMath::RandRange(50.f, SphereRadius);
}

FVector ASphereSpawnZone::FindPlaceForNextSphere()
{
	//Flag for "While"
	bool PlaceNotFound{true};
	
	int32 Iter{ 0 };

	//Get Random Unit Vector of SphereSpawnZone
	FVector RandVector = GetActorLocation() + rand.GetUnitVector() * GetRandDistanceForSpherePlace();

	//If count of Z smaller then 0. Multiply to (-1)
	if (RandVector.Z < 0)
	{
		RandVector.Z *= -1;
	}

	//Cycle to find place of SphereTarget 
	while (PlaceNotFound)
	{

		for (auto& Elem : HandlerATargetLocation)
		{
			++Iter;
			const float Distance = FVector::Dist(RandVector, HandlerATargetLocation[Elem.Key]->GetActorLocation());

			if (Distance < DistanceBetweenSphereTarget)
			{
				Iter = 0;
				
				RandVector = GetActorLocation() + rand.GetUnitVector() * GetRandDistanceForSpherePlace();
				if (RandVector.Z < 0)
				{
					RandVector.Z *= -1;
				}
				break;
			}
			else if (Iter == HandlerATargetLocation.Num())
			{
				PlaceNotFound = false;
			}
		}
	}
	return RandVector;
}

void ASphereSpawnZone::CalculateScore()
{
	++Score;
	OnScoreChange.Broadcast();
}

