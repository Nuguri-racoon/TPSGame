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

}

// Called to bind functionality to input
void ABaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseEnemy::SetEnemyState_Implementation(EEnemyState NewState)
{
}

EEnemyState ABaseEnemy::GetEnemyState_Implementation() const
{
	return EEnemyState();
}

FVector ABaseEnemy::GetTargetLocation_Implementation() const
{
	return FVector();
}

bool ABaseEnemy::isDead_Implementation() const
{
	return false;
}

bool ABaseEnemy::CanTakeCover_Implementation() const
{
	return false;
}

void ABaseEnemy::Damage_Implementation(float Damage)
{
}


