// Fill out your copyright notice in the Description page of Project Settings.

#include "AI_EnemeyController.h"                       
#include "DrawDebugHelpers.h"                           
#include "BehaviorTree/BehaviorTree.h"                  
#include "BehaviorTree/BlackboardData.h"               
#include "BehaviorTree/BlackboardComponent.h"           
#include "Perception/AIPerceptionComponent.h"          
#include "Perception/AISenseConfig_Sight.h"           
#include "Perception/AISenseConfig_Hearing.h"          
#include "Perception/AISenseConfig_Damage.h"            
#include "Perception/AIPerceptionSystem.h"            
#include "Kismet/GameplayStatics.h"                    

const FName AAI_EnemeyController::StartPosKey = TEXT("Startpoint"); // 시작 위치 키 이름
const FName AAI_EnemeyController::PatrolPosKey = TEXT("PatrolPos"); // 순찰 위치 키 이름
const FName AAI_EnemeyController::TargetActorKey = TEXT("TargetActor"); // 타겟 액터 키 이름
const FName AAI_EnemeyController::PlayerPointKey = TEXT("PlayerPoint"); // 소리 위치 키 이름

AAI_EnemeyController::AAI_EnemeyController()
{
    static ConstructorHelpers::FObjectFinder<UBehaviorTree> btree(TEXT("/Game/Enemy/BT-Enemy.BT-Enemy"));
    if (btree.Succeeded())
    {
        BeTree = btree.Object;
    }

    static ConstructorHelpers::FObjectFinder<UBlackboardData> data(TEXT("/Game/Enemy/BB-Enemy.BB-Enemy")); 
    if (data.Succeeded()) 
    {
        BlackData = data.Object;
    }

    PerceptComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception")); 
    SetPerceptionComponent(*PerceptComp);

    sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight"));
    sight->SightRadius = 1000.0f; //시야거리
    sight->LoseSightRadius = sight->SightRadius + 500.0f; //시야잃는거리설정
    sight->PeripheralVisionAngleDegrees = 90.0f; //시야각 설정
    sight->SetMaxAge(5.0f); // 사거리유효시간
    sight->AutoSuccessRangeFromLastSeenLocation = -1.f; 
    //추후변경필요
    sight->DetectionByAffiliation.bDetectEnemies = true; // 적 감지 허용
    sight->DetectionByAffiliation.bDetectNeutrals = true; // 중립 감지 허용
    sight->DetectionByAffiliation.bDetectFriendlies = true; // 아군 감지 허용

    PerceptComp->ConfigureSense(*sight); //시야 등록
    PerceptComp->SetDominantSense(sight->GetSenseImplementation());
    
    hearing = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing"));
    hearing->HearingRange = 800.f; //소리 감지 거리 설정
    hearing->SetMaxAge(3.0f); //소리 정보 유효 시간 설정
    hearing->DetectionByAffiliation.bDetectEnemies = true; //적 감지 허용
    hearing->DetectionByAffiliation.bDetectNeutrals = true; //중립 감지 허용
    hearing->DetectionByAffiliation.bDetectFriendlies = true; //아군 감지 허용
    PerceptComp->ConfigureSense(*hearing); //청각 등록

    damage = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("Damage")); 
    damage->SetMaxAge(4.0f);
    PerceptComp->ConfigureSense(*damage);

    PerceptComp->OnPerceptionUpdated.AddDynamic(this, &AAI_EnemeyController::PerceptionUpdated); // 여러 액터 콜백 바인드

    PerceptComp->OnTargetPerceptionUpdated.AddDynamic(this, &AAI_EnemeyController::OnTargetPerceptionUpdated); // 한 액터 콜백 바인드
}

void AAI_EnemeyController::OnPossess(APawn* pawn)
{
    Super::OnPossess(pawn); 

    UBlackboardComponent* blackCom = Blackboard;
    if (UseBlackboard(BlackData, blackCom))
    {
        Blackboard->SetValueAsVector(StartPosKey, pawn->GetActorLocation());
        if (!RunBehaviorTree(BeTree))
        {
            UE_LOG(TPSGAME, Log, TEXT("Fail BehaviorTree"));
        }
    }

#ifdef DEBUG_DRAW
    DrawDebugSphere(GetWorld(), pawn->GetActorLocation(), sight->SightRadius, 20, FColor::Green, false, 5.0f); 
    DrawDebugSphere(GetWorld(), pawn->GetActorLocation(), hearing->HearingRange, 20, FColor::Green, false, 5.0f); 
    DrawDebugSphere(GetWorld(), pawn->GetActorLocation(), sight->LoseSightRadius, 20, FColor::Red, false, 5.0f);
#endif
}

//인지할게 여러개일경우
void AAI_EnemeyController::PerceptionUpdated(const TArray<AActor*>& UpdatedActors) 
{
    for (AActor* UpdateActor : UpdatedActors)
    {
        if (!UpdateActor)
        {
            continue;
        }

        FAIStimulus AISTimulus = CanSenseActor(UpdateActor, EEnemyPerception::Sight);
        if (AISTimulus.WasSuccessfullySensed())
        {
            HandleSensedSight(UpdateActor);
            continue;
        }

        FAIStimulus HearStim = CanSenseActor(UpdateActor, EEnemyPerception::Hearing);
        if (HearStim.WasSuccessfullySensed())
        {
            HandleSensedHearing(HearStim.StimulusLocation);
            continue;
        }
        FAIStimulus DamageStim = CanSenseActor(UpdateActor, EEnemyPerception::Damage);
        if (DamageStim.WasSuccessfullySensed())
        {
            HandleSensedDamage(UpdateActor);
            continue;
        }

        //안전코드
        if (Blackboard && Cast<AActor>(Blackboard->GetValueAsObject(TargetActorKey)) == UpdateActor) 
        {
            Blackboard->ClearValue(TargetActorKey); // 블랙보드 타겟 클리어
            UE_LOG(TPSGAME, Log, TEXT("Cleared TargetActor because actor no longer sensed: %s"), *UpdateActor->GetName()); 
        }
    }
}
//단일일경우
void AAI_EnemeyController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus) 
{
    if (!Actor) return; 

    TSubclassOf<UAISense> SenseClass = UAIPerceptionSystem::GetSenseClassForStimulus(GetWorld(), Stimulus); 
    if (SenseClass == UAISense_Sight::StaticClass())
    {
        if (Stimulus.WasSuccessfullySensed())
        {
            HandleSensedSight(Actor);
        }
        else 
        {
            if (Blackboard && Cast<AActor>(Blackboard->GetValueAsObject(TargetActorKey)) == Actor) 
            {
                Blackboard->ClearValue(TargetActorKey);
                UE_LOG(TPSGAME, Log, TEXT("OnTargetPerceptionUpdated: Cleared TargetActor (lost sight): %s"), *Actor->GetName());
            }
        }
    }
    else if (SenseClass == UAISense_Hearing::StaticClass())
    {
        if (Stimulus.WasSuccessfullySensed()) 
        {
            HandleSensedHearing(Stimulus.StimulusLocation);
        }
    }
    else if (SenseClass == UAISense_Damage::StaticClass())
    {
        if (Stimulus.WasSuccessfullySensed())
        {
            HandleSensedDamage(Actor);
        }
    }
}

//플레이어가 없어졌을때,마지막 감각 유지
FAIStimulus AAI_EnemeyController::CanSenseActor(AActor* Actor, EEnemyPerception SenseType)
{
    FActorPerceptionBlueprintInfo ActorPercetionInfo; //퍼셉션 정보를 담을 구조체
    FAIStimulus ResultStimulus; //결과로 반환할 자극 (기본값은 빈 자극)

    if (!Actor || !PerceptComp)
    {
        return ResultStimulus;
    }

    if (!PerceptComp->GetActorsPerception(Actor, ActorPercetionInfo)) return ResultStimulus;

    TSubclassOf<UAISense> SenseClass;
    switch (SenseType)
    {
    case EEnemyPerception::None:
        break; 
    case EEnemyPerception::Sight:
        SenseClass = UAISense_Sight::StaticClass();
        break;
    case EEnemyPerception::Hearing:
        SenseClass = UAISense_Hearing::StaticClass();
        break;
    case EEnemyPerception::Damage:
        SenseClass = UAISense_Damage::StaticClass();
        break;
    default:
        break;
    }

    for (const FAIStimulus& Stimulus : ActorPercetionInfo.LastSensedStimuli)//마지막감각반복
    {
        TSubclassOf<UAISense> LastSensed = UAIPerceptionSystem::GetSenseClassForStimulus(GetWorld(), Stimulus); // 자극의 Sense 클래스 가져오기
        if (SenseClass == LastSensed) 
        {
            return Stimulus; // 해당 자극 반환
        }
    }

    return ResultStimulus;
}

//시야핸들
void AAI_EnemeyController::HandleSensedSight(AActor* Actor)
{
    if (!Actor) return;
    if (!Blackboard) return;

    APawn* PlayerPawn = Cast<APawn>(Actor); 
    bool bIsPlayer = false; 

    if (PlayerPawn && PlayerPawn->IsPlayerControlled())
    {
        bIsPlayer = true;
    }
    else if (Actor->ActorHasTag(TEXT("Player"))) //사용할 플레이어에 태그 추가해야함
    {
        bIsPlayer = true;
    }

    if (bIsPlayer)
    {
        Blackboard->SetValueAsObject(TargetActorKey, Actor);
        UE_LOG(TPSGAME, Log, TEXT("HandleSensedSight: Player detected and set as TargetActor: %s"), *Actor->GetName());
    }
    else//플레이어가 아닌경우 추가 필요
    {
        UE_LOG(TPSGAME, Log, TEXT("HandleSensedSight: Non-player actor seen: %s"), *Actor->GetName());
    }
}

void AAI_EnemeyController::HandleSensedHearing(const FVector& NoiseLocation)
{
    if (!Blackboard) return;
    Blackboard->SetValueAsVector(PlayerPointKey, NoiseLocation);
    UE_LOG(TPSGAME, Log, TEXT("HandleSensedHearing: Heard noise at %s"), *NoiseLocation.ToString());
}

void AAI_EnemeyController::HandleSensedDamage(AActor* Actor)
{
    if (!Actor) return;
    if (!Blackboard) return;
    Blackboard->SetValueAsObject(TargetActorKey, Actor);
    UE_LOG(TPSGAME, Log, TEXT("HandleSensedDamage: Actor set as TargetActor: %s"), *Actor->GetName());
}
