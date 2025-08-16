// Fill out your copyright notice in the Description page of Project Settings.


#include "FindAnySynesthesia.h"
#include "../AI_EnemeyController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UFindAnySynesthesia::OnBecomeRelevant(UBehaviorTreeComponent& OwnerCom, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerCom, NodeMemory);

	UBlackboardComponent* blackCom = OwnerCom.GetBlackboardComponent();
	if (!blackCom) return;

	//유저타겟 블랙보드세팅
	AActor* TargetPlayer = Cast<AActor>(blackCom->GetValueAsObject(AAI_EnemeyController::TargetActorKey));

	if (TargetPlayer)
	{

	}
	else
	{

	}
}
