// Fill out your copyright notice in the Description page of Project Settings.



#include "Controller/Enemy/NightAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/Enemy/NightEnemyBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/CrowdFollowingComponent.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISenseConfig_Sight.h"

ANightAIController::ANightAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{
	PrimaryActorTick.bCanEverTick = true;
	
	AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("EnemySenseConfig_Sight");
	AISenseConfig_Damage = CreateDefaultSubobject<UAISenseConfig_Damage>("EnemySenseConfig_Damage");
	
	// 감지 설정 구성
	AISenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true; // 적 감지 활성화
	AISenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false; // 아군 감지 비활성화
	AISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false; // 중립 대상 감지 비활성화
	
	// 시야 파라미터 설정
	AISenseConfig_Sight->SightRadius = 1000.f; // 최대 감지 거리
	AISenseConfig_Sight->LoseSightRadius = 1100.f; // 감지 상실 거리
	AISenseConfig_Sight->PeripheralVisionAngleDegrees = 180.f; // 완전한 360도 시야각

	// AI 감지 컴포넌트 생성 및 설정
	EnemyPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("EnemyPerceptionComponent");
	EnemyPerceptionComponent->ConfigureSense(*AISenseConfig_Sight); 
	EnemyPerceptionComponent->ConfigureSense(*AISenseConfig_Damage);
	EnemyPerceptionComponent->SetDominantSense(AISenseConfig_Sight->GetSenseImplementation()); // 시야 감각을 주요 감각으로 설정
	
	// 감지 업데이트 이벤트 바인딩
	EnemyPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ThisClass::OnEnemyPerceptionUpdated);
	EnemyPerceptionComponent->OnTargetPerceptionForgotten.AddDynamic(this,&ANightAIController::OnTargetPerceptionForgotten);
	SetGenericTeamId(FGenericTeamId(1));
}

ETeamAttitude::Type ANightAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	// 전달된 액터를 Pawn 타입으로 캐스팅
	const APawn* PawnToCheck = Cast<const APawn>(&Other);

	// Pawn의 컨트롤러에서 Generic Team Agent 인터페이스를 가져옴
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<IGenericTeamAgentInterface>(PawnToCheck->GetController());

	// 다른 팀이라면 적대적 관계로 간주
	if (OtherTeamAgent && OtherTeamAgent->GetGenericTeamId() < GetGenericTeamId())
	{
		return ETeamAttitude::Hostile;
	}

	// 기본적으로 우호적 관계로 반환
	return ETeamAttitude::Friendly;
}

void ANightAIController::OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (!GetBlackboardComponent())
	{
		return;
	}
	
	if (static_cast<EEnemyState>(GetBlackboardComponent()->GetValueAsEnum(FName("State"))) == EEnemyState::Dead)
	{
		return;
	}
	
	//시야에서 적을 발견하면 난 전투상태가 될거야!
	if (Stimulus.WasSuccessfullySensed() && Actor)
	{
		TargetActor = Actor;
		GetBlackboardComponent()->SetValueAsEnum(FName("State"),static_cast<uint8>(EEnemyState ::Combat));
		GetBlackboardComponent()->SetValueAsObject(FName("TargetActor"), Actor);
	}
	else
	{
		GetBlackboardComponent()->ClearValue(FName("TargetActor"));
	}
	
}

void ANightAIController::OnTargetPerceptionForgotten(AActor* Actor)
{
	//감지를 놓친 액터가 타겟액터라면
	if (TargetActor == Actor)
	{
		GetBlackboardComponent()->SetValueAsEnum(FName("State"),static_cast<uint8>(EEnemyState ::Idle));
	}
}

void ANightAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	checkf(BehaviorTreeToRun, TEXT("BehaviorTreeToRun is nullptr. Current object: %s"), *GetName());
	
	RunBehaviorTree(BehaviorTreeToRun);
	if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
    {
        BlackboardComponent->SetValueAsVector(FName("StartLocation"), InPawn->GetActorLocation());

		 ACharacter* EnemyCharacter = Cast<ACharacter>(InPawn);
		BlackboardComponent->SetValueAsFloat(FName("DefaultMaxWalkSpeed"), EnemyCharacter->GetCharacterMovement()->MaxWalkSpeed);
		PosseedAIPawn = Cast<ANightEnemyBase>(GetPawn()); 
    }
}


