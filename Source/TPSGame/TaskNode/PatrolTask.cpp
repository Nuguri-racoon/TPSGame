// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolTask.h"
#include "../AI_EnemeyController.h"
#include "NavigationSystem.h"
#include "../BaseEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UPatrolTask::ExecuteTask(UBehaviorTreeComponent& OwnerCom, uint8* NodeMemory)
{
	EBTNodeResult::Type res = Super::ExecuteTask(OwnerCom, NodeMemory);

	auto pawn = OwnerCom.GetAIOwner()->GetPawn();

	if (pawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	UNavigationSystemV1* nav = UNavigationSystemV1::GetNavigationSystem(pawn->GetWorld());
	if(nav == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	FVector startPos = OwnerCom.GetBlackboardComponent()->GetValueAsVector(AAI_EnemeyController::StartPosKey);
	FNavLocation pos;
	if(nav->GetRandomPointInNavigableRadius(startPos, 300.0f, pos))
	{
		OwnerCom.GetBlackboardComponent()->SetValueAsVector(AAI_EnemeyController::PatrolPosKey, pos.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
