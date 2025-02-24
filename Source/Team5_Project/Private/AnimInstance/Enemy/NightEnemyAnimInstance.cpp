// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimInstance/Enemy/NightEnemyAnimInstance.h"

#include "KismetAnimationLibrary.h"
#include "Character/NightCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

UNightEnemyAnimInstance::UNightEnemyAnimInstance()
{
}

void UNightEnemyAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<ANightCharacterBase>(TryGetPawnOwner());

	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UNightEnemyAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningMovementComponent)
	{
		return;
	}

	GroundSpeed = OwningCharacter->GetVelocity().Size2D();

	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;

	LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(OwningCharacter->GetVelocity(),OwningCharacter->GetActorRotation());
}

bool UNightEnemyAnimInstance::DoesOwnerHaveTag(FName TagToCheck) const
{
	return TryGetPawnOwner()->ActorHasTag(TagToCheck);
}
