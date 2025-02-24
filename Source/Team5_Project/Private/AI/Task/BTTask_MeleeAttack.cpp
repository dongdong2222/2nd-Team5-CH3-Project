// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_MeleeAttack.h"

#include "AIController.h"
#include "Character/Enemy/NightEnemyBase.h"

UBTTask_MeleeAttack::UBTTask_MeleeAttack()
{
	NodeName = TEXT("MeleeAttack");
	bNotifyTaskFinished = true;
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	// AI 컨트롤러가 없는 경우 실패로 간주
	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	// AI의 소유 캐릭터를 ANightEnemyBase로 캐스팅
	NightEnemyCharacter = Cast<ANightEnemyBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (NightEnemyCharacter == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	// 공격 종료 이벤트 추가
	// 몽타주가 종료되면 공격 종료 이벤트를 호출
	NightEnemyCharacter->OnAttackEnded.AddUniqueDynamic(this, &UBTTask_MeleeAttack::OnAttackEnded);

	// 근접 공격 실행
	NightEnemyCharacter->MeleeAttack(MontageTag);
	CachedOwnerComp = &OwnerComp;
	
	return EBTNodeResult::InProgress;
}

void UBTTask_MeleeAttack::OnAttackEnded()
{
	if (NightEnemyCharacter)
	{
		// 공격 종료 이벤트 바인딩 해제
		NightEnemyCharacter->OnAttackEnded.RemoveDynamic(this, &UBTTask_MeleeAttack::OnAttackEnded);
	}

	if (CachedOwnerComp)
	{
		// 작업 완료로 설정
		FinishLatentTask(*CachedOwnerComp, EBTNodeResult::Succeeded);
	}
}
