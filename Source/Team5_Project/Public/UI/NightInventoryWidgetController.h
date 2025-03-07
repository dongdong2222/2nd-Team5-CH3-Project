// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/NightWidgetController.h"
#include "Inventory/NightInventorySystem.h"
#include "NightInventoryWidgetController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeInventorySignature, UNightInventorySystem*, InventorySystem);

/**
 * 
 */
UCLASS()
class TEAM5_PROJECT_API UNightInventoryWidgetController : public UNightWidgetController
{
	GENERATED_BODY()
public:
	void InitInventoryWidgetController(UNightInventorySystem* InInventorySystem);

	//interface of NightWidgetController
	virtual void BroadcastInitialValue();
	virtual void BindCallbackToDependencies();
	//End of NightWidgetController
protected:
	UNightInventorySystem* InventorySystem;

	UPROPERTY(BlueprintAssignable)
	FOnChangeInventorySignature OnInventoryChange;

private:
	void InventoryChanged();
};
