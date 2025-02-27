// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Enemy/NightEnemyBase.h"
#include "NightSevarog.generated.h"


UENUM(BlueprintType)
enum class ESevarogAttackMode : uint8
{
	None UMETA(DisplayName = "None"),
	StandardCombo UMETA(DisplayName = "Standard Combo"),
	SwingInAir UMETA(DisplayName = "Swing In Air"),
	SoulSiphon UMETA(DisplayName = "Soul Siphon"),
	Ultimate UMETA(DisplayName = "Ultimate")
};

/**
 * 
 */
UCLASS()
class TEAM5_PROJECT_API ANightSevarog : public ANightEnemyBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat")
	ESevarogAttackMode AttackMode;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat")
	bool IsAttacking;

	//데미지를 받으면 플레이어를 봄
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat")
	bool ShouldFacePlayer;
	
	//데미지를 받으면 플레이어를 봄
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat")
	bool LookAtPlayer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat")
	bool CanSeePlayer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	bool IsDead;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Misc")
	FVector LastHammerLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Misc")
	FVector HammerVelocity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Emitter")
	UParticleSystem* GhostHandParticleSystem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat")
	float DamageAmount;

	
	ANightSevarog();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void Fire_SoulSiphon();
	
};
