// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "NightEnemyAnimInstance.generated.h"

class ANightCharacterBase;
struct FGameplayTag;
class UCharacterMovementComponent;
class ANightCharacter;
/**
 * 
 */
UCLASS()
class TEAM5_PROJECT_API UNightEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UNightEnemyAnimInstance();
	
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Ref")
	ANightCharacterBase* OwningCharacter;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Ref")
	UCharacterMovementComponent* OwningMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Ref")
	ANightCharacterBase* TargetCharacter;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "AnimData|LocomotionData")
	float GroundSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "AnimData|LocomotionData")
	bool bHasAcceleration;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "AnimData|LocomotionData")
	float LocomotionDirection;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "AnimData|LocomotionData")
	float Angle;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "FaceAO")
	float FacePitch;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "FaceAO")
	float FaceYaw;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	bool IsDead;
	
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	bool DoesOwnerHaveTag(FName TagToCheck) const;
};
