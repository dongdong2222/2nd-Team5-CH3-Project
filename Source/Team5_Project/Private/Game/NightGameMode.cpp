// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/NightGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Game/NightGameInstance.h"
#include "Character/Player/NightPlayerCharacter.h"
#include "DataAsset/NightPlayerDataAsset.h"

ANightGameMode::ANightGameMode()
{
	/*
	DefaultPawnClass = ANightCharacter::StaticClass();
	PlayerControllerClass = ANightPlayerController::StaticClass();
	GameStateClass = ANightaGameState::StaticClass();
	*/
}

void ANightGameMode::HandlePlayerDeath(ACharacter* DeadCharacter)
{
    UE_LOG(LogTemp, Warning, TEXT("HandlePlayerDeath() called: Restarting Level after delay..."));

    float DeathAnimationDuration = 2.0f; 

    GetWorldTimerManager().SetTimer(AutoDeathTimer, this, &ANightGameMode::RestartLevel, DeathAnimationDuration, false);
}

void ANightGameMode::RestartLevel()
{
    UWorld* World = GetWorld();
    if (!World)
    {
        UE_LOG(LogTemp, Error, TEXT("RestartLevel() failed: GetWorld() returned NULL!"));
        return;
    }

    UNightGameInstance* GI = Cast<UNightGameInstance>(UGameplayStatics::GetGameInstance(this));
    if (!GI || !GI->LevelNames.IsValidIndex(GI->CurrentLevelIndex))
    {
        UE_LOG(LogTemp, Error, TEXT("RestartLevel() failed: Invalid CurrentLevelIndex or GameInstance is NULL!"));
        return;
    }

    FString RestartLevelName = GI->LevelNames[GI->CurrentLevelIndex];

    UE_LOG(LogTemp, Warning, TEXT("RestartLevel(): Restarting Level %s"), *RestartLevelName);

    ANightPlayerCharacter* PlayerCharacter = Cast<ANightPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(World, 0));
    if (PlayerCharacter)
    {
        if (PlayerCharacter->StatData)
        {
            UNightPlayerDataAsset* PlayerDataAsset = Cast<UNightPlayerDataAsset>(PlayerCharacter->StatData);
            if (PlayerDataAsset)
            {
                PlayerDataAsset->SetStemina(PlayerDataAsset->GetMaxStemina());
                UE_LOG(LogTemp, Warning, TEXT("RestartLevel(): PlayerDataAsset stamina reset to max."));
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("RestartLevel(): PlayerDataAsset is NULL after casting StatData!"));
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("RestartLevel(): PlayerCharacter's StatData is NULL!"));
        }
        PlayerCharacter->GetWorldTimerManager().ClearTimer(PlayerCharacter->SteminaTimer);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("RestartLevel(): PlayerCharacter is NULL!"));
    }


    UGameplayStatics::OpenLevel(GetWorld(), FName(*RestartLevelName));
}