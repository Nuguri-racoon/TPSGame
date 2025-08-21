// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "PatrolTask.generated.h"

/**
 * 
 */
UCLASS()
class TPSGAME_API UPatrolTask : public UBTTaskNode
{
	GENERATED_BODY()
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerCom, uint8* NodeMemory) override;
};
