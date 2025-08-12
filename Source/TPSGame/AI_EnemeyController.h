// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TPSGame.h"
#include "AIController.h"
#include "AI_EnemeyController.generated.h"

/**
 * 
 */
UCLASS()
class TPSGAME_API AAI_EnemeyController : public AAIController
{
	GENERATED_BODY()
	UPROPERTY()
	TObjectPtr<class UBehaviorTree> BeTree{};
	UPROPERTY()
	TObjectPtr<class UBlackboardData> BlackData{};

public:
	AAI_EnemeyController();
	virtual void OnPossess(APawn* pawn)override;

	static const FName StartPosKey;
	static const FName PatrolPosKey;
	
};
