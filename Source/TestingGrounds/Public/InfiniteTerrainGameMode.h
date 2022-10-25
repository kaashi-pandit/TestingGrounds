// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestingGrounds/TestingGroundsGameMode.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "InfiniteTerrainGameMode.generated.h"


/**
 * 
 */
UCLASS()
class TESTINGGROUNDS_API AInfiniteTerrainGameMode : public ATestingGroundsGameMode
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Bounds Pool")
	void PopulateBoundsVolumePool();

private:
	void AddToPool(ANavMeshBoundsVolume* VolumeToAdd);
};