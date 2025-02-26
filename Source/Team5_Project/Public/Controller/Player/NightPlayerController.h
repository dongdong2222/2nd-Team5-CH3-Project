// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"
#include "NightPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class TEAM5_PROJECT_API ANightPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* TurnAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* CrouchAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* RollingAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* ReloadAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* AimAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* ShotAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* ESCAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* UsePotionAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* ThrowAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* InteractionAction;
public:
	ANightPlayerController();

	virtual void BeginPlay() override;
	//~IGenericTeamAgentInterface inteface
	virtual FGenericTeamId GetGenericTeamId() const override;
	//End of ~IGenericTeamAgentInterface inteface

private:
	FGenericTeamId playerTeamId;
private:
	void SetInputMapping(const UInputMappingContext* MappingContext);
};
