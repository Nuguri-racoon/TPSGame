// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TPSGame.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimPlay.generated.h"

/**
 * 
 */
UCLASS()
class TPSGAME_API UEnemyAnimPlay : public UAnimInstance
{
	GENERATED_BODY()

private:

	
protected:
	UPROPERTY(BlueprintReadOnly)
	float m_fX{};
	UPROPERTY(BlueprintReadOnly)
	float m_fY{};
	UPROPERTY(BlueprintReadOnly)
	bool m_isDead = false;
	UPROPERTY(BlueprintReadOnly)
	bool m_isMovable = true; //∞»±‚√º≈©


public:
	UEnemyAnimPlay();
	void SetX(float x);
	void SetY(float y);

	
};
