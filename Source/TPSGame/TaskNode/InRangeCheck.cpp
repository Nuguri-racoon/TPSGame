// Fill out your copyright notice in the Description page of Project Settings.


#include "InRangeCheck.h"
#include "../AI_EnemeyController.h"
#include "../BaseEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../AttackInterface.h"

bool UInRangeCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerCom, uint8* NodeMemory) const
{
	bool res = Super::CalculateRawConditionValue(OwnerCom, NodeMemory);
	AAIController* AICont = OwnerCom.GetAIOwner();
	if (!AICont) return false;

	APawn* AIpawn = AICont->GetPawn();
	if (AIpawn == nullptr) return false;

	ABaseEnemy* Enemy = Cast<ABaseEnemy>(AIpawn);

	UBlackboardComponent* BlackboardComp = OwnerCom.GetBlackboardComponent();
	if (!BlackboardComp) return false;

	AActor* Target = Cast<AActor>(BlackboardComp->GetValueAsObject(AAI_EnemeyController::TargetActorKey));
	if (Target == nullptr) return false;

	float dist = FVector::Dist(AIpawn->GetActorLocation(), Target->GetActorLocation());
	return dist <= 600.f;

}
