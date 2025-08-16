// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../TPSGame.h"
#include "BehaviorTree/BTService.h"
#include "FindAnySynesthesia.generated.h"

/**
 * 
 */
UCLASS()
class TPSGAME_API UFindAnySynesthesia : public UBTService
{
	GENERATED_BODY()

	public:
		virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerCom, uint8* NodeMemory) override;
};
