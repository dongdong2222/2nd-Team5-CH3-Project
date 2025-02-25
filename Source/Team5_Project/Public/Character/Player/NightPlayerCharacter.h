// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/NightCharacterBase.h"
#include "GameplayTagContainer.h"
#include "NightPlayerCharacter.generated.h"

struct FInputActionValue;
class ANightWeaponBase;
/**
 * 
 */
UCLASS()
class TEAM5_PROJECT_API ANightPlayerCharacter : public ANightCharacterBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category="State")
	FGameplayTagContainer PlayerStateTags;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* RollingMontage;

	UPROPERTY(EditAnywhere, Category = "Animation")
	TSubclassOf<UAnimInstance> Pistol;

	UPROPERTY(EditAnywhere, Category = "Animation")
	TSubclassOf<UAnimInstance> Rifle;

	UPROPERTY(EditAnywhere, Category = "Animation")
	TSubclassOf<UAnimInstance> Shotgun;

public:
	ANightPlayerCharacter();
	//~APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//End of ~APawn interface

private:
	TArray<TSubclassOf<ANightWeaponBase>> QuickSlot;
	int32 CurrentSlot;

private:
	//InputAction
	// - locomotion
	void Move(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);
	void SwitchCrouch(const FInputActionValue& Value);
	void StartSprint(const FInputActionValue& Value);
	void EndSprint(const FInputActionValue& Value);
	void Rolling(const FInputActionValue& Value);
	// - ÃÑ°ü·Ã
	void Reload(const FInputActionValue& Value);
	void Aim(const FInputActionValue& Value);
	void Shot(const FInputActionValue& Value);
	void SwitchWeapon(const FInputActionValue& Value);
	// - ±âÅ¸
	void ESC(const FInputActionValue& Value);
	void UsePotion(const FInputActionValue& Value);
	void Throw(const FInputActionValue& Value);
	void Interaction(const FInputActionValue& Value);
	//End of InputAction

	void SetFirstPersonView();
	void SetThirdPersonView();

	void SetWeaponToPlayerHand();
	void AddToCurrentSlot(float value);
	
};
