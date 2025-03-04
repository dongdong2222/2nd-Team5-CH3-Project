// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NightWidgetController.generated.h"

/**
 * 
 */
UCLASS()
class TEAM5_PROJECT_API UNightWidgetController : public UObject
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValue();
	virtual void BindCallbackToDependencies();
protected:
	//if there are some default property for WidgetController,
	//add to here

};
