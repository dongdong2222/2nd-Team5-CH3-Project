// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FPlayerItemDataRow.generated.h"

class ANightWeaponBase;
class UNightPlayerAnimInstance;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FPlayerItemDataRow : public FTableRowBase
{
  GENERATED_BODY()
public:
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  TSubclassOf<ANightWeaponBase> WeaponClass;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  TSubclassOf<UAnimInstance> AnimLayer;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  UAnimMontage* EquipMontage;
};
