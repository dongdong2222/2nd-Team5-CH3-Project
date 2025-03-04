// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NightHUD.generated.h"

class UNightInventoryWidgetController;
class UNightInventorySystem;
class UNightUserWidget;

/**
 * 
 */
UCLASS()
class TEAM5_PROJECT_API UNightHUD : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void InitInventory(UNightInventorySystem* InventorySystem);
	UFUNCTION(BlueprintCallable)
	void RemoveInventory();

	UNightInventoryWidgetController* GetInventoryWidgetController(UNightInventorySystem* InventorySystem);

public:
	TObjectPtr<UNightInventoryWidgetController> InventoryWidgetController;
	TObjectPtr<UNightUserWidget> InventoryWidget;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UNightInventoryWidgetController> InventoryWidgetControllerClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UNightUserWidget> InventoryWidgetClass;
	
};
