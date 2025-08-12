// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseMonster.h"
#include "Gunner_Enemy.generated.h"

class UCapsuleComponent;

UCLASS()
class TPSGAME_API AGunner_Enemy : public ABaseMonster
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* skMesh{};
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* capCom{};


public:
	// Sets default values for this pawn's properties
	AGunner_Enemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
