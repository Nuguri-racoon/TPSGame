// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "enumEnemyState.h"
#include "AttackInterface.h"
#include "BaseMonster.generated.h"

UCLASS()
class TPSGAME_API ABaseMonster : public APawn, public IIAIInter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseMonster();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster", meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 100.0f;
	float CurrentHealth{};
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	//Interface
	void SetEnemyState_Implementation(EEnemyState NewState) override; //현재상변경 시
	EEnemyState GetEnemyState_Implementation()const override;		  //현재상태 가져오기
	FVector GetTargetLocation_Implementation()const override;		  //플레이어 위치 
	bool isDead_Implementation()const override;						  //죽음여부
	bool CanTakeCover_Implementation()const override;				  //엄폐가능여부
	void Damage_Implementation(float Damage)override;				  //데미지주기



};
