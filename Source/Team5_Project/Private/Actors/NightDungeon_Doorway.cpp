// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/NightDungeon_Doorway.h"

ANightDungeon_Doorway::ANightDungeon_Doorway()
{
	PrimaryActorTick.bCanEverTick = true;

	DoorRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DoorRoot"));
	SetRootComponent(DoorRoot);

	DoorwayMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorwayMesh"));
	DoorwayMesh->SetupAttachment(DoorRoot);

	LeftDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftDoor"));
	LeftDoor->SetupAttachment(DoorwayMesh);

	RightDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightDoor"));
	RightDoor->SetupAttachment(DoorwayMesh);
}


