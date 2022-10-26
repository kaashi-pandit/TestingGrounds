#include "ActorPool.h"

UActorPool::UActorPool()
{
	PrimaryComponentTick.bCanEverTick = true;
}

AActor* UActorPool::CheckOut()
{
	return nullptr;
}

void UActorPool::Return(AActor* ActorToReturn)
{
}

void UActorPool::Add(AActor* ActorToAdd)
{
}
