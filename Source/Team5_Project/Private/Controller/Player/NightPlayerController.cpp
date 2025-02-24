// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/Player/NightPlayerController.h"

ANightPlayerController::ANightPlayerController()
{
	playerTeamId = FGenericTeamId(0);
}

FGenericTeamId ANightPlayerController::GetGenericTeamId() const
{
	return playerTeamId;
}
