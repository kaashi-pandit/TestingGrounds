#include "ChooseNextWaypoint.h"
#include "AIController.h"
//#include "PatrollingGuard.h"
#include "PatrolRoute.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get the patrol points	
	const auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	const auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();

	if (!ensure(PatrolRoute))
	{
		return EBTNodeResult::Failed;
	}
	auto PatrolPoints = PatrolRoute->GetPatrolPoints();

	if (PatrolPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("A guard is missing patrol points"));
		return EBTNodeResult::Failed;
	}
	
	//Set next waypoint
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	const int32 KeyIndex = BlackboardComp->GetValueAsInt(BlackboardKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[KeyIndex]);

	//Cycle the Index
	const auto NextIndex = (KeyIndex + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(BlackboardKey.SelectedKeyName, NextIndex);
	
	return EBTNodeResult::Succeeded;
}
