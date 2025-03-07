// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CheckEnemyState.generated.h"

enum class EEnemyState : uint8;
/**
 * 
 */
UCLASS()
class TEAM5_PROJECT_API UBTDecorator_CheckEnemyState : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_CheckEnemyState();

	// 체크할 적 상태 (예: Dead, Idle 등)
	UPROPERTY(EditAnywhere, Category = "Enemy State")
	EEnemyState DesiredState;

protected:
	// 데코레이터 조건 평가 함수
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

};
