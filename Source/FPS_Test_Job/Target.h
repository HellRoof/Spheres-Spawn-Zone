// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Target.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSphereDestroyedDelegate, int32, TargetID);

UCLASS()
class FPS_TEST_JOB_API ATarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	int32 TargetID= 0;

	UPROPERTY(VisibleAnywhere)
	FSphereDestroyedDelegate OnSphereDestroyed;

	UPROPERTY(VisibleAnywhere)
		class USphereComponent* SphereCollision;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* SphereMesh;

	UPROPERTY(EditAnywhere, Category = "Effects")
		UParticleSystem* DeathPatricle; //Death effect

	float SphereRadius; 

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void DestroyFunction();
	
};
