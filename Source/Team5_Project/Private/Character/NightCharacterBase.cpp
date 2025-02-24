// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NightCharacterBase.h"

#include "MotionWarpingComponent.h"



// Sets default values
ANightCharacterBase::ANightCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	MaxHealth = 10.f;
	Health = MaxHealth;

	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
}


