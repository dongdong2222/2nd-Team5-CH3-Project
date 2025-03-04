// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NightInventoryWidgetController.h"

void UNightInventoryWidgetController::InitInventoryWidgetController(UNightInventorySystem* InInventorySystem)
{
  InventorySystem = InInventorySystem;
}

void UNightInventoryWidgetController::BroadcastInitialValue()
{
}

void UNightInventoryWidgetController::BindCallbackToDependencies()
{
  if (!InventorySystem) return;
  InventorySystem->OnInventoryChange.AddDynamic(this, &ThisClass::InventoryChanged);
}

void UNightInventoryWidgetController::InventoryChanged()
{
  OnInventoryChange.Broadcast(InventorySystem);
}
