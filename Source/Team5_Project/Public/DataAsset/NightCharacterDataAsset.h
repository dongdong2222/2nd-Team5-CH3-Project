// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NightCharacterDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class TEAM5_PROJECT_API UNightCharacterDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UNightCharacterDataAsset();
	float GetHealth() const;
	void SetHealth(float value);

	float GetMaxHealth() const;
	void SetMaxHealth(float value);

	float GetDefence() const;
	void SetDefence(float value);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MaxHealth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float Defence;
};
