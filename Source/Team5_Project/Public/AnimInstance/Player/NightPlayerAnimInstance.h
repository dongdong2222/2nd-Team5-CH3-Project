// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "NightPlayerAnimInstance.generated.h"

class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class TEAM5_PROJECT_API UNightPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "Rotation")
	FRotator WorldRotation;

	UPROPERTY(BlueprintReadWrite, Category = "Rotation")
	FRotator ControllerRotation;

	UPROPERTY(BlueprintReadWrite, Category = "Rotation")
	FRotator DeltaRotation;

	UPROPERTY(BlueprintReadWrite, Category = "Rotation")
	FRotator RotationForAim;

	UPROPERTY(BlueprintReadWrite, Category="Velocity")
	FVector WorldVelocity;

	UPROPERTY(BlueprintReadWrite, Category = "Velocity")
	FVector LocalVelocity;

	UPROPERTY(BlueprintReadWrite, Category = "Velocity")
	float GroundSpeed;

	UPROPERTY(BlueprintReadWrite, Category = "Velocity")
	float WorldMoveDirection;

	UPROPERTY(BlueprintReadWrite, Category = "Velocity")
	float LocalMoveDirection;

	UPROPERTY(BlueprintReadWrite, Category = "Aim")
	FVector ScreenCenterWorldLocation;

	UPROPERTY(BlueprintReadWrite, Category = "Aim")
	FRotator WorldWeaponRotation;

	UPROPERTY(BlueprintReadWrite, Category = "Rolling")
	FVector WorldRollingDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rolling")
	UAnimMontage* InPlaceMontage;

public:
	// ~UAnimInstance inteface
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	// End of ~UAnimInstance inteface

protected:
	ACharacter* Character;
	UCharacterMovementComponent* MovementComponent;

protected:
	void UpdateRotation();
	void UpdateVelocity();
	void UpdateAim(float DeltaTime);
	void UpdateRolling(float DeltaTime);

};
