#include "Terrain.h"
#include "DrawDebugHelpers.h"

// Sets default values
ATerrain::ATerrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATerrain::BeginPlay()
{
	Super::BeginPlay();

	CanSpawnAtLocation(GetActorLocation(), 300);
}

void ATerrain::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	
	for (size_t i = 0; i < NumberToSpawn; i++)
	{
		FVector SpawnPoint;
		float RandScale = FMath::RandRange(MinScale, MaxScale);
		bool Found = FindEmptyLocation(SpawnPoint, Radius * RandScale);
		
		if (Found)
		{
			float RandomRotation = FMath::FRandRange(-180, 180);
			PlaceActor(ToSpawn, SpawnPoint, RandomRotation, RandScale);
		}

		//UE_LOG(LogTemp, Warning, TEXT("SpawnPoint: %s"), *SpawnPoint.ToCompactString());
	}	
}

void ATerrain::PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint, float Rotation, float Scale)
{
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	Spawned->SetActorRelativeLocation(SpawnPoint);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	Spawned->SetActorRotation(FRotator(0,Rotation, 0));
	Spawned ->SetActorScale3D(FVector(Scale));
}

bool ATerrain::FindEmptyLocation(FVector& OutLocation, float Radius)
{
	FBox Bounds(MinArea, MaxArea);

	const int MAX_ATTEMPTS = 100;
	for (size_t i = 0; i < MAX_ATTEMPTS; i++)
	{
		FVector CandidatePoint = FMath::RandPointInBox(Bounds);

		if (CanSpawnAtLocation(CandidatePoint, Radius))
		{
			OutLocation = CandidatePoint;	
			return true;
		}
	}
	return false;
}

bool ATerrain::CanSpawnAtLocation(FVector Location, float Radius)
{	
	FHitResult HitResult;

	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);

	bool HasHit = GetWorld()->SweepSingleByChannel
	(
		HitResult,
		GlobalLocation,
		GlobalLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(Radius)
	);

	FColor ResultColor = HasHit ? FColor::Red : FColor::Green;

	if (HasHit)
	{
		auto NameHai = HitResult.GetActor()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Hit hua actor: %s"), *NameHai);
	}

	DrawDebugCapsule
	(
		GetWorld(),
		GlobalLocation,	
		0,
		Radius,
		FQuat::Identity,
		ResultColor,
		true,
		100
	);
	
	return !HasHit;
}

// Called every frame
void ATerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

