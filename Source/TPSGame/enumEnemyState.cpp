// Fill out your copyright notice in the Description page of Project Settings.


#include "enumEnemyState.h"

// Sets default values
AenumEnemyState::AenumEnemyState()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EnemyState = EEnemyState::Idle; // 초기 상태를 Idle로 설정
}

// Called when the game starts or when spawned
void AenumEnemyState::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AenumEnemyState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

