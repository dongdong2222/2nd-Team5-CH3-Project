// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimInstance/Enemy/NightEnemyAnimInstance.h"

#include "AIController.h"
#include "KismetAnimationLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/NightCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

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

	Angle = UKismetMathLibrary::FindLookAtRotation(OwningCharacter->GetActorForwardVector(), OwningCharacter->GetVelocity()).Yaw;
	
	AAIController* AIController = Cast<AAIController>(OwningCharacter->GetController());
	if (AIController)
	{
		UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent();
		if (BlackboardComp)
		{
			if (BlackboardComp->GetValueAsObject(FName("TargetActor"))) 
			{
				TargetCharacter = Cast<ANightCharacterBase>(BlackboardComp->GetValueAsObject(FName("TargetActor")));
			}
		}
	}

	if (TargetCharacter)
	{
		FVector DirectionUnitVector = UKismetMathLibrary::GetDirectionUnitVector(GetOwningActor()->GetActorLocation(),TargetCharacter->GetActorLocation());
		FRotator NormalizeRotator = UKismetMathLibrary::NormalizedDeltaRotator(GetOwningActor()->GetActorRotation(),DirectionUnitVector.ToOrientationRotator());
		FaceYaw = NormalizeRotator.GetInverse().Yaw;
		FacePitch = NormalizeRotator.GetInverse().Pitch;
	}
	
}

bool UNightEnemyAnimInstance::DoesOwnerHaveTag(FName TagToCheck) const
{
	return TryGetPawnOwner()->ActorHasTag(TagToCheck);
}
