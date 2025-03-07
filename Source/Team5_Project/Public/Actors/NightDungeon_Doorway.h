// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NightDungeon_Doorway.generated.h"

UCLASS()
class TEAM5_PROJECT_API ANightDungeon_Doorway : public AActor
{
	GENERATED_BODY()
	
public:	
	ANightDungeon_Doorway();

	UFUNCTION(BlueprintImplementableEvent, Category = "Door Actions")
	void OpenDoors();
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
    USceneComponent* DoorRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* DoorwayMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* LeftDoor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* RightDoor;
	
	
};
