// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NightInventorySystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChange);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEAM5_PROJECT_API UNightInventorySystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNightInventorySystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY()
	FOnInventoryChange OnInventoryChange;

		
};
