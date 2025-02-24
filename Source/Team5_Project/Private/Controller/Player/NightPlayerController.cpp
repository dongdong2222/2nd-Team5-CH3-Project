// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/Player/NightPlayerController.h"
#include "EnhancedInputSubsystems.h"

ANightPlayerController::ANightPlayerController()
{
  playerTeamId = FGenericTeamId(0);
}

void ANightPlayerController::BeginPlay()
{
  SetInputMapping(DefaultMappingContext);
}

FGenericTeamId ANightPlayerController::GetGenericTeamId() const
{
  return playerTeamId;
}

void ANightPlayerController::SetInputMapping(const UInputMappingContext* MappingContext)
{
  ULocalPlayer* LocalPlayer = GetLocalPlayer();
  if (!LocalPlayer) return;
  UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
  if (!Subsystem) return;

  if (MappingContext)
  {
    Subsystem->AddMappingContext(MappingContext, 0);
  }
}
