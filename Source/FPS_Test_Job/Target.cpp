// Fill out your copyright notice in the Description page of Project Settings.

#include "UObject/UObjectBase.h"

#include "Target.h"
#include "SphereSpawnZone.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATarget::ATarget()
{
	// Use a sphere as a simple collision representation
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->InitSphereRadius(60.0f);
	SphereCollision->SetCollisionProfileName("Trigger");
	RootComponent = SphereCollision;

	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	SphereMesh->SetupAttachment(RootComponent);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ATarget::OnOverlapBegin);
}

void ATarget::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		DestroyFunction();
	}
}

void ATarget::DestroyFunction()
{
	//Spawn destroy effect
	UGameplayStatics::SpawnEmitterAtLocation(this, DeathPatricle, GetActorLocation());
	
	Destroy();

	//Get Unique target id
	TargetID = this->GetUniqueID();
	
	//Delegate
	OnSphereDestroyed.Broadcast(TargetID);
}

