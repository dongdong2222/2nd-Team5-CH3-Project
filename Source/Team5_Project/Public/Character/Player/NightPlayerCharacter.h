// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/NightCharacterBase.h"
#include "GameplayTagContainer.h"
#include "NightPlayerCharacter.generated.h"

struct FInputActionValue;
//struct FPlayerItemDataRow;
class ANightWeaponBase;
/**
 * 
 */
UCLASS()
class TEAM5_PROJECT_API ANightPlayerCharacter : public ANightCharacterBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="State")
	FGameplayTagContainer PlayerStateTags;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* RollingMontage;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* ThrowMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QuickSlot")
	TArray<FName> QuickSlot;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Weapon")
	ANightWeaponBase* CurrentWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<ANightWeaponBase> PrevWeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	ANightWeaponBase* PrevWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 CurrentSlot;

	FTimerHandle SteminaTimer;
	FTimerHandle SprintTimer;

public:
	UFUNCTION()
	//Bind to Anim Notify
	void SetWeaponToPlayerHand();
	// End of Bind to Anim Notify

	UFUNCTION(BlueprintImplementableEvent)
	void SetFirstPersonView();

	void SetThirdPersonView();

	UFUNCTION(BlueprintCallable)
	void Dead(FVector Direction);

	UFUNCTION(BlueprintCallable)
	FVector GetTargetLocation();

	ANightPlayerCharacter();
	//~APawn interface
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//End of ~APawn interface

	UFUNCTION(BlueprintImplementableEvent)
	void K2_SwitchWeapon();
	UFUNCTION(BlueprintImplementableEvent)
	void K2_Reload();

	UFUNCTION(BlueprintImplementableEvent)
	void Interaction(const FInputActionValue& Value);


private:
	UFUNCTION()
	void OnMontageStart(UAnimMontage* Montage);
	UFUNCTION()
	void OnMontageEnd(UAnimMontage* Montage, bool bInterrupted);


	//InputAction
	// - locomotion
	void Move(const FInputActionValue& Value);
	void EndMove(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);
	void SwitchCrouch(const FInputActionValue& Value);
	void StartOnceSprint(const FInputActionValue& Value);
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

	//End of InputAction



	void AddToCurrentSlot(float value);


	
};
