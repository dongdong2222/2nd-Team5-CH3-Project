// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "NightPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class TEAM5_PROJECT_API ANightPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "HealPotion")
	int32 MaxHealPotionCount;
	UPROPERTY(EditAnywhere, Category = "HealPotion")
	int32 CurrentHealPotionCount;
	UPROPERTY(EditAnywhere, Category = "HealPotion")
	float HealAmount;

public:
	UFUNCTION(BlueprintCallable, Category = "HealPotion")
	void UseHealPotion();

	
};
