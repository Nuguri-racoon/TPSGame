// Fill out your copyright notice in the Description page of Project Settings.

#include "Gunner_Enemy.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AGunner_Enemy::AGunner_Enemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	capCom = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));
	capCom->SetupAttachment(RootComponent);
	capCom->SetCapsuleSize(35.f, 90.f);
	//콜리전추가 필요

	skMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SKMESH"));
	skMesh->SetupAttachment(capCom);
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> res(TEXT("/Game/ParagonMurdock/Characters/Heroes/Murdock/Skins/CS_MatteBlack/Mesh/Murdock_SF.Murdock_SF"));
	if (res.Succeeded())
	{
		skMesh->SetSkeletalMesh(res.Object);
	}
	//콜리전 사이즈 늘리고 캐릭터 회전 및 아래로 내리기
}

// Called when the game starts or when spawned
void AGunner_Enemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGunner_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGunner_Enemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

