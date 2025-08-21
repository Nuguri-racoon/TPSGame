// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackTask.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"   
#include "../AttackInterface.h"
#include "../BaseEnemy.h"
#include "../AI_EnemeyController.h"

EBTNodeResult::Type UAttackTask::ExecuteTask(UBehaviorTreeComponent& OwnerCom, uint8* NodeMemory)
{
	EBTNodeResult::Type res = Super::ExecuteTask(OwnerCom, NodeMemory); 

	ABaseEnemy* enemy = Cast<ABaseEnemy>(OwnerCom.GetAIOwner()->GetPawn());

	if (enemy && enemy->GetClass()->ImplementsInterface(UAIInter::StaticClass()))
	{
		IAIInter::Execute_SetEnemyState(enemy, EEnemyState::Attack);
	}
	enemy->OnAttack(); 

	return EBTNodeResult::Succeeded;
}


