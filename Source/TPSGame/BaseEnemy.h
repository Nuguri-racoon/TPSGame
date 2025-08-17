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
class TPSGAME_API ABaseEnemy : public ACharacter, public IIAIInter
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
	EEnemyState CurrentState{ EEnemyState::Idle };
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health{ 100.0f };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float DeathTimer{ 3.0f };
	float CurrentDeathTime{ 0.0f };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	bool isDead{ false };

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Interface
	void SetEnemyState_Implementation(EEnemyState NewState) override; 
	EEnemyState GetEnemyState_Implementation()const override;		 
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
	bool isMovable = true;
};
