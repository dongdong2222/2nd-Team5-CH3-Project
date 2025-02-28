// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "NightGameState.generated.h"

/**
 * 
 */
UCLASS()
class TEAM5_PROJECT_API ANightGameState : public AGameState
{
	GENERATED_BODY()

public:
	ANightGameState();

	// Á×Àº È½¼ö
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	int32 DeathCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	float LevelStartTime;

	// ÇöÀç ·¹º§
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Level")
	//int32 CurrentLevelIndex;

	//  ·¹º§ ÀÌµ¿ Æ®¸®°Å ¿À¹ö·¦ È½¼ö
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Level")
	int32 OverlapTriggerCount;

	//FTimerHandle LevelTimerHandle;

public:
	virtual void BeginPlay() override;
	void OnPlayerDeath();
	void EndLevel();
	void OnGameFinished();

	UFUNCTION(BlueprintCallable, Category = "Level")
	void IncreaseOverlapTriggerCount();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void LoadNextLevel();
	
};
