// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "enumEnemyState.generated.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle UMETA(DisplayName = "Idel"),			//대기
	Patrol UMETA(DisplayName = "Patrol"),		//정찰
	Alert UMETA(DisplayName = "Alert"),			//경계(소리용)
	Chase UMETA(DisplayName = "Chase"),			//추적
	Attack UMETA(DisplayName = "Attack"),		//공격
	Cover UMETA(DisplayName = "Cover"),			//엄폐
	Dead UMETA(DisplayName = "Dead")			//죽음

};


UCLASS()
class TPSGAME_API AenumEnemyState : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AenumEnemyState();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	EEnemyState EnemyState;
};
