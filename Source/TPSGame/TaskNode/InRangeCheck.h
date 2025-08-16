// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "InRangeCheck.generated.h"

/**
 * 
 */
UCLASS()
class TPSGAME_API UInRangeCheck : public UBTDecorator
{
	GENERATED_BODY()

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerCom, uint8* NodeMemory) const override;
	
};
