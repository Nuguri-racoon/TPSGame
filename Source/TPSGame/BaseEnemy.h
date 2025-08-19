// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TPSGame.h"
#include "GameFramework/Character.h"
#include "enumEnemyState.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"  
#include "AttackInterface.h"
#include "BaseEnemy.generated.h"

UCLASS()
class TPSGAME_API ABaseEnemy : public ACharacter, public IAIInter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	EEnemyState CurrentState{ EEnemyState::Idle }; //현재 상태 기계
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health{ 100.0f };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float DeathTimer{ 3.0f };
	float CurrentDeathTime{ 0.0f };
	UPROPERTY(BlueprintReadWrite, Category = "AI")
	bool m_isDead{ false };

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Interface
	void SetEnemyState_Implementation(EEnemyState NewState) override; //상태기계설정하기
	EEnemyState GetEnemyState_Implementation()const override;		  //상태기계가져오기
	FVector GetTargetLocation_Implementation()const override;		  
	bool isDead_Implementation()const override;						 
	bool CanTakeCover_Implementation()const override;	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Damage(float Damage);
	void Damage_Implementation(float Damage)override;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnAttack();
	virtual void OnAttack_Implementation();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* attMont;
	bool m_isMovable = true;
};
