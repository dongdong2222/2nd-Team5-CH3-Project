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
	// 세바로그의 공격 모드
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat")
	ESevarogAttackMode AttackMode;

	// 현재 공격 중인지 여부
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat")
	bool IsAttacking; 

	// 데미지를 받으면 플레이어를 바라보는지 여부
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat")
	bool ShouldFacePlayer;
	
	// 플레이어를 바라보는 상태인지 여부
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat")
	bool LookAtPlayer;

	// 플레이어를 볼 수 있는 상태인지 여부
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat")
	bool CanSeePlayer;
	
	// 마지막 망치의 위치
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Misc")
	FVector LastHammerLocation;

	// 망치의 이동 속도
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Misc")
	FVector HammerVelocity;

	// 유령 손 파티클 시스템
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Emitter")
	UParticleSystem* GhostHandParticleSystem;
	
	ANightSevarog();

	// 영혼 착취공격
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void Fire_SoulSiphon();
	
};
