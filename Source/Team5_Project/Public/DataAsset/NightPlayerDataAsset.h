// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/NightCharacterDataAsset.h"
#include "NightPlayerDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class TEAM5_PROJECT_API UNightPlayerDataAsset : public UNightCharacterDataAsset
{
	GENERATED_BODY()
public:
	float GetStemina() const;
	void SetStemina(float value);

	float GetMaxStemina() const;
	void SetMaxStemina(float value);

	float GetWalkSpeed() const;
	void SetWalkSpeed(float value);

	float GetSprintSpeed() const;
	void SetSprintSpeed(float value);

	float GetDashCost() const;
	void SetDashCost(float value);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float Stemina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MaxStemina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float WalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float SprintSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float DashCost;
	
};
