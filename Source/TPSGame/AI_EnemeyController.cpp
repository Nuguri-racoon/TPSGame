// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_EnemeyController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AAI_EnemeyController::StartPosKey = TEXT("Startpoint");
const FName AAI_EnemeyController::PatrolPosKey = TEXT("PatrolPos");

AAI_EnemeyController::AAI_EnemeyController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> btree(TEXT("/Game/Enemy/BT-Enemy.BT-Enemy"));
	if (btree.Succeeded())
	{
		BeTree = btree.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBlackboardData> data(TEXT("/Game/Enemy/BB-Enemy.BB-Enemy"));
	if (data.Succeeded())
	{
		BlackData = data.Object;
	}
}

void AAI_EnemeyController::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);

	UBlackboardComponent* blackCom = Blackboard;
	if (UseBlackboard(BlackData,blackCom))
	{
		Blackboard->SetValueAsVector(StartPosKey, pawn->GetActorLocation());
		if (!RunBehaviorTree(BeTree))
		{
			UE_LOG(TPSGAME, Log, TEXT("Fail BehviorTree"));
		}
	}
}
