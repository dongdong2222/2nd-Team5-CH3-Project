// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/Enemy/NightWolf.h"

#include "Components/BoxComponent.h"

ANightWolf::ANightWolf()
{
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(GetMesh());
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
}
