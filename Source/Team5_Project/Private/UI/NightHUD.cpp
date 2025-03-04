// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NightHUD.h"
#include "UI/NightInventoryWidgetController.h"
#include "Inventory/NightInventorySystem.h"
#include "UI/NightUserWidget.h"

void UNightHUD::InitInventory(UNightInventorySystem* InventorySystem)
{
  InventoryWidget = CreateWidget<UNightUserWidget>(GetWorld(), InventoryWidgetClass);

  GetInventoryWidgetController(InventorySystem);

  InventoryWidget->SetWidgetController(InventoryWidgetController);
  InventoryWidgetController->BroadcastInitialValue();
  InventoryWidget->AddToViewport();
}

void UNightHUD::RemoveInventory()
{
  InventoryWidget->RemoveFromParent();
}

UNightInventoryWidgetController* UNightHUD::GetInventoryWidgetController(UNightInventorySystem* InventorySystem)
{
  if (!InventoryWidgetController) return InventoryWidgetController;
  
  InventoryWidgetController = NewObject<UNightInventoryWidgetController>(this, InventoryWidgetControllerClass);

  InventoryWidgetController->InitInventoryWidgetController(InventorySystem);
  InventoryWidgetController->BindCallbackToDependencies();
  return InventoryWidgetController;
}
