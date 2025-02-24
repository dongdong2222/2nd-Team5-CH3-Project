// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MeleeAttack.generated.h"

class ANightEnemyBase;
/**
 * 
 */
UCLASS()
class TEAM5_PROJECT_API UBTTask_MeleeAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_MeleeAttack();


protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UFUNCTION()
	void OnAttackEnded();

private:
	UPROPERTY()
	ANightEnemyBase* NightEnemyCharacter;
	UPROPERTY()
	UBehaviorTreeComponent* CachedOwnerComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite ,Category = "Montage", meta = (DisplayName = "Montage Tag", AllowPrivateAccess = "true"))
	FName MontageTag;
};
