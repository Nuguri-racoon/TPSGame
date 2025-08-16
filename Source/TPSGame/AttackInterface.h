// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TPSGame.h"
#include "enumEnemyState.h"
#include "UObject/Interface.h"
#include "AttackInterface.generated.h"

UINTERFACE(MinimalAPI,Blueprintable)
class UIAIInter : public UInterface
{
	GENERATED_BODY()
};
class IIAIInter
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetEnemyState(EEnemyState NewState);  //상태기계설정하기
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	EEnemyState GetEnemyState() const;						//상태기계가져오기

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FVector GetTargetLocation() const;					//Player위치추적
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool isDead() const;					//죽었는지 여부
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool CanTakeCover() const; 				//엄폐가능여부	

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Damage(float Damage);			//데미지주기

	



};

