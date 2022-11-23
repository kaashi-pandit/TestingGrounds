// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorPool.h"
#include "Terrain.generated.h"

USTRUCT()
struct FSpawnPostion
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FVector Location;

	UPROPERTY()
	float Rotation;

	UPROPERTY()
	float Scale;
};

UCLASS()
class TESTINGGROUNDS_API ATerrain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATerrain();

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale);

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void PlaceAIPawns(TSubclassOf<APawn> ToSpawn, int MinSpawn, int MaxSpawn, float Radius);

	void PlaceAIPawn(TSubclassOf<APawn>& ToSpawn, FSpawnPostion& SpawnPoint);


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

	void PlaceActor(TSubclassOf<AActor> ToSpawn, FSpawnPostion& SpawnPos);

	TArray<FSpawnPostion> RandomSpawnPositions(int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale);

	UPROPERTY(EditAnyWhere, Category = "SpawnArea")
	FVector MinArea {0,-2000,0};

	UPROPERTY(EditAnyWhere, Category = "SpawnArea")
	FVector MaxArea {4000, 2000, 0};
	
	UPROPERTY(EditDefaultsOnly, Category = "Navigation")
	FVector NavigationBoundOffset;

private:

	bool CanSpawnAtLocation(FVector Location, float Radius);

	UActorPool* Pool;

	AActor* NavMeshBoundsVolume;
};
