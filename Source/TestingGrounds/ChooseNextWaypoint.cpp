// Fill out your copyright notice in the Description page of Project Settings.


#include "ChooseNextWaypoint.h"

#include "AIController.h"
#include "PatrollingGuard.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get the patrol points
	const auto AIController = OwnerComp.GetAIOwner();
	const auto ControlledPawn = AIController->GetPawn();
	const auto PatrollingGuard = Cast<APatrollingGuard>(ControlledPawn);
	auto PatrolPoints = PatrollingGuard->PatrolPointsCPP;

	//Set next waypoint
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	const int32 KeyIndex = BlackboardComp->GetValueAsInt(BlackboardKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[KeyIndex]);

	//Cycle the Index
	const auto NextIndex = (KeyIndex + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(BlackboardKey.SelectedKeyName, NextIndex);
	
	return EBTNodeResult::Succeeded;
}
