// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator/BTDecorator_CheckEnemyState.h"

#include "AIController.h"
#include "Character/Enemy/NightEnemyBase.h"

UBTDecorator_CheckEnemyState::UBTDecorator_CheckEnemyState()
{
	NodeName = TEXT("Check Enemy State");
	
}

bool UBTDecorator_CheckEnemyState::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = false;
	
	if (AAIController* AIController = OwnerComp.GetAIOwner())
	{
		if (APawn* Pawn = AIController->GetPawn())
		{
			if (ANightEnemyBase* Enemy = Cast<ANightEnemyBase>(Pawn))
			{
				bResult = (Enemy->EnemyState == DesiredState);
			}
		}
	}
	
	return bResult;
}
