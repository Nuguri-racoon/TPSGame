// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurrentState == EEnemyState::Dead)
	{
		CurrentDeathTime += DeltaTime;
		AddActorWorldOffset(FVector(0.0f, 0.0f, -20.0f * DeltaTime));

		if (CurrentDeathTime >= DeathTimer)
		{
			Destroy();
		}
	}

}

// Called to bind functionality to input
void ABaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseEnemy::SetEnemyState_Implementation(EEnemyState NewState)
{
	CurrentState = NewState;
}

EEnemyState ABaseEnemy::GetEnemyState_Implementation() const
{
	return CurrentState;
}

FVector ABaseEnemy::GetTargetLocation_Implementation() const
{
	return GetActorLocation();
}

bool ABaseEnemy::isDead_Implementation() const
{
	return CurrentState == EEnemyState::Dead;
}

bool ABaseEnemy::CanTakeCover_Implementation() const
{
	return false;
}

void ABaseEnemy::Damage_Implementation(float Damage)
{
	Health -= Damage;
	if (Health <= 0.0f)
	{
		SetEnemyState(EEnemyState::Dead);
	}
}

void ABaseEnemy::OnAttack_Implementation()
{
}



