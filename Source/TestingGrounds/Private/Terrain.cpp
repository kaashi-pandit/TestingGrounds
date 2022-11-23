#include "Terrain.h"
#include "NavigationSystem.h"
#include "DrawDebugHelpers.h"


// Sets default values
ATerrain::ATerrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NavigationBoundOffset = FVector(2000,0,0);
}

void ATerrain::BeginPlay()
{
	Super::BeginPlay();	

	CanSpawnAtLocation(GetActorLocation(), 300);
}

void ATerrain::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	Pool->Return(NavMeshBoundsVolume);	
}

TArray<FSpawnPostion> ATerrain::RandomSpawnPositions(int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	TArray<FSpawnPostion> SpawnPositions;
	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);

	for (size_t i = 0; i < NumberToSpawn; i++)
	{
		FSpawnPostion SpawnPosition;
		SpawnPosition.Scale = FMath::RandRange(MinScale, MaxScale);
		bool Found = FindEmptyLocation(SpawnPosition.Location, Radius * SpawnPosition.Scale);

		if (Found)
		{
			SpawnPosition.Rotation = FMath::FRandRange(-180, 180);
			SpawnPositions.Add(SpawnPosition);
			//PlaceActor(ToSpawn, SpawnPosition);
		}
	}
	return SpawnPositions;
}


void ATerrain::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	TArray<FSpawnPostion> SpawnPos = RandomSpawnPositions(MinSpawn, MaxSpawn, Radius, MinScale, MaxScale);
	for (auto SpawnPoint : SpawnPos)
	{
		PlaceActor(ToSpawn, SpawnPoint);
	}
}

void ATerrain::PlaceAIPawns(TSubclassOf<APawn> ToSpawn, int MinSpawn, int MaxSpawn, float Radius)
{
	TArray<FSpawnPostion> AISpawnPos = RandomSpawnPositions(MinSpawn, MaxSpawn, Radius, 1,1);
	for (auto SpawnPoint : AISpawnPos)
	{
		PlaceAIPawn(ToSpawn, SpawnPoint);
	}
}

void ATerrain::PlaceAIPawn(TSubclassOf<APawn>& ToSpawn, FSpawnPostion& SpawnPoint)
{
	APawn* Spawned = GetWorld()->SpawnActor<APawn>(ToSpawn);
	Spawned->SetActorRelativeLocation(SpawnPoint.Location);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	Spawned->SetActorRotation(FRotator(0, SpawnPoint.Rotation, 0));
	Spawned->SpawnDefaultController();
	Spawned->Tags.Add(FName("Enemy"));
}

void ATerrain::PlaceActor(TSubclassOf<AActor> ToSpawn, FSpawnPostion& SpawnPos)
{
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	Spawned->SetActorRelativeLocation(SpawnPos.Location);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	Spawned->SetActorRotation(FRotator(0, SpawnPos.Rotation, 0));
	Spawned->SetActorScale3D(FVector(SpawnPos.Scale));
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

void ATerrain::SetPool(UActorPool* InPool)
{
	UE_LOG(LogTemp, Warning, TEXT("[%s] Setting Pool %s"), *(this->GetName()), *(InPool->GetName()));
	Pool = InPool;

	PositionNavMeshBoundsVolume();
}

void ATerrain::PositionNavMeshBoundsVolume()
{
	NavMeshBoundsVolume = Pool->CheckOut();
	if (NavMeshBoundsVolume == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] Not enough actors in pool"), *GetName());
		return;
	}
	UE_LOG(LogTemp, Error, TEXT("[%s] Checked out: %s"), *GetName(), *NavMeshBoundsVolume->GetName());
	NavMeshBoundsVolume->SetActorLocation(GetActorLocation() + NavigationBoundOffset);
	auto Nav1 = Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem());
	Nav1->Build();

	UE_LOG(LogTemp, Error, TEXT("BUILD NAVMESH !!"));
	
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

