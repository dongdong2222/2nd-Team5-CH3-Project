// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"
#include "NightPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TEAM5_PROJECT_API ANightPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
public:
	ANightPlayerController();

	//~IGenericTeamAgentInterface inteface
	virtual FGenericTeamId GetGenericTeamId() const override;
	//End of ~IGenericTeamAgentInterface inteface

	

private:
	FGenericTeamId playerTeamId;
};
