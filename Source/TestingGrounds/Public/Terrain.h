// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorPool.h"
#include "Terrain.generated.h"


UCLASS()
class TESTINGGROUNDS_API ATerrain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATerrain();

	UFUNCTION(BlueprintCallable, Category = "Randomness")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn = 1, int MaxSpawn = 1, float Radius = 150, float MinScale = 1, float MaxScale = 1);

	void PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint, float Rotation, float Scale);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool FindEmptyLocation(FVector& OutLocation, float Radius);

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void SetPool(UActorPool* Pool);

	void PositionNavMeshBoundsVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditAnyWhere, Category = "SpawnArea")
	FVector MinArea {0,-2000,0};

	UPROPERTY(EditAnyWhere, Category = "SpawnArea")
	FVector MaxArea {4000, 2000, 0};
	
private:

	bool CanSpawnAtLocation(FVector Location, float Radius);

	UActorPool* Pool;

	AActor* NavMeshBoundsVolume;
};
