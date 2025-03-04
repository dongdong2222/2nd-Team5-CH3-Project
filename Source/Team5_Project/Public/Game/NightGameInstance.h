// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NightGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TEAM5_PROJECT_API UNightGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UNightGameInstance();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	TArray<int32> LevelDeathCounts; // 레벨 별 죽은 횟수

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	TArray<float> LevelClearTimes; // 레벨 별 클리어 시간

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	int32 TotalDeathCount; // 총 죽은 횟수

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	float TotalClearTime; // 게임 클리어까지 걸린 시간

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Level")
	int32 CurrentLevelIndex; // 현재 레벨

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	TArray<FString> LevelNames; // 레벨 이름

	static const int32 MaxLevels = 2;

public:
	UFUNCTION(BlueprintCallable, Category = "GameData")
	void AddDeathCount(int32 DeathCount); // 모든 레벨에서 죽은 횟수 더하기

	UFUNCTION(BlueprintCallable, Category = "GameData")
	void AddTotalTime(float TimeCount); // 게임 클리어까지 걸린 시간 구하기(클리어 실패했던 레벨의 시간도 전부 포함)

	UFUNCTION(BlueprintCallable, Category = "Game")
	FString GetNextLevelName(); // 레벨 이름 얻기 

	void SaveLevelStats(float ClearTime, int32 DeathCount); //최종 결과

};
