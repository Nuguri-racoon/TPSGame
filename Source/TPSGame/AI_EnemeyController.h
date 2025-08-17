// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TPSGame.h"
#include "AIController.h"
#include "enumEnemyState.h" 
#include "AI_EnemeyController.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class UAISenseConfig_Hearing;
class UAISenseConfig_Damage;

UCLASS()
class TPSGAME_API AAI_EnemeyController : public AAIController
{

	GENERATED_BODY()

private:
	UPROPERTY()
	TObjectPtr<class UBehaviorTree> BeTree{};
	UPROPERTY()
	TObjectPtr<class UBlackboardData> BlackData{};
public:
	UFUNCTION()
	void PerceptionUpdated(const TArray<AActor*>& UpdatedActors);
	UFUNCTION()                                        // 바인드용 마커
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	FAIStimulus CanSenseActor(AActor* Actor, EEnemyPerception SenseType);
	void HandleSensedSight(AActor* Actor);             // 시야 감지 처리 함수
	void HandleSensedHearing(const FVector& NoiseLocation); // 소리 감지 처리 함수
	void HandleSensedDamage(AActor* Actor);

public:
	UPROPERTY(BlueprintReadOnly, Category = "AI")
	TObjectPtr<class UAIPerceptionComponent> PerceptComp{};
	UPROPERTY(BlueprintReadWrite, Category = "AI")	
	UAISenseConfig_Sight* sight{}; 
	UPROPERTY(BlueprintReadWrite, Category = "AI")
	UAISenseConfig_Hearing* hearing{}; 
	UPROPERTY(BlueprintReadWrite, Category = "AI")
	UAISenseConfig_Damage* damage{};


public:

	AAI_EnemeyController();
	virtual void OnPossess(APawn* pawn)override;

	static const FName StartPosKey;
	static const FName PatrolPosKey;
	static const FName TargetActorKey;
	static const FName PlayerPointKey;
};
