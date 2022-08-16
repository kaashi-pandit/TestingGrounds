// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Terrain.generated.h"

UCLASS()
class TESTINGGROUNDS_API ATerrain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATerrain();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Randomness")
	void PlaceActors();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnyWhere, Category = "SpawnArea")
	FVector MinArea {0,-2000,0};

	UPROPERTY(EditAnyWhere, Category = "SpawnArea")
	FVector MaxArea {4000, 2000, 0};
	

};
