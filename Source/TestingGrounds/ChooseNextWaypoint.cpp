// Fill out your copyright notice in the Description page of Project Settings.


#include "ChooseNextWaypoint.h"

#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	if (BlackboardComp != nullptr)
	{
		const int32 KeyIndex = BlackboardComp->GetValueAsInt(BlackboardKey.SelectedKeyName);
		UE_LOG(LogTemp, Warning, TEXT("Waypoint index : %i"), KeyIndex);
	}
	return EBTNodeResult::Succeeded;
}
