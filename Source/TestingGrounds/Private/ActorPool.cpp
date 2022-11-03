#include "ActorPool.h"

UActorPool::UActorPool()
{
	PrimaryComponentTick.bCanEverTick = true;
}

AActor* UActorPool::CheckOut()
{
	UE_LOG(LogTemp, Warning, TEXT("%s Checkout"), *GetName());
	return nullptr;
}

void UActorPool::Return(AActor* ActorToReturn)
{
	if (ActorToReturn)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Actor returned: %s"), *GetName(), *ActorToReturn->GetName());
	}
}

void UActorPool::Add(AActor* ActorToAdd)
{
	if (ActorToAdd)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Actor Add: %s"), *GetName(), *ActorToAdd->GetName());
	}
}
