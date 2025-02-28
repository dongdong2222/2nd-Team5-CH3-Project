// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/NightGameInstance.h"

UNightGameInstance::UNightGameInstance()
{
    TotalDeathCount = 0;
    TotalClearTime = 0.0f;
    CurrentLevelIndex = 0;
    LevelDeathCounts.Init(0, MaxLevels);
    LevelClearTimes.Init(0.0f, MaxLevels);

    if (LevelNames.Num() == 0)
    {
        LevelNames = { TEXT("Valley_Demonstration"), TEXT("MainLevel") };
    }
}

void UNightGameInstance::AddDeathCount(int32 DeathCount)
{
    LevelDeathCounts[CurrentLevelIndex] += DeathCount;

}

void UNightGameInstance::AddTotalTime(float TimeCount)
{
    LevelClearTimes[CurrentLevelIndex] = +TimeCount;

}

FString UNightGameInstance::GetNextLevelName()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("instance getnextlevelname")));

    UE_LOG(LogTemp, Warning, TEXT("LevelNames Array Size: %d"), LevelNames.Num());
    UE_LOG(LogTemp, Warning, TEXT("CurrentLevelIndex: %d"), CurrentLevelIndex);

    if (LevelNames.IsValidIndex(CurrentLevelIndex))
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("isvalid")));

        return LevelNames[CurrentLevelIndex + 1];
    }
    UE_LOG(LogTemp, Error, TEXT("Not Valid"));
    return FString();
}

void UNightGameInstance::SaveLevelStats(float ClearTime, int32 DeathCount)
{
    if (LevelDeathCounts.IsValidIndex(CurrentLevelIndex) && LevelClearTimes.IsValidIndex(CurrentLevelIndex))
    {
        LevelClearTimes[CurrentLevelIndex] = ClearTime;
        LevelDeathCounts[CurrentLevelIndex] = DeathCount;
    }

    TotalClearTime += ClearTime;
    TotalDeathCount += DeathCount;
}
