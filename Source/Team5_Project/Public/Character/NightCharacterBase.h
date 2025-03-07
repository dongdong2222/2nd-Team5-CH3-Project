// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NightCharacterBase.generated.h"

class UMotionWarpingComponent;
class UNightCharacterDataAsset;

UCLASS()
class TEAM5_PROJECT_API ANightCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ANightCharacterBase();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stat")
	UNightCharacterDataAsset* StatData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="MotionWarping")
	UMotionWarpingComponent* MotionWarpingComponent;
	


protected:
	int32 Health;
	int32 MaxHealth;
	
};
