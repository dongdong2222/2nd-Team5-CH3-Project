// Fill out your copyright notice in the Description page of Project Settings.


#include "Notify/NightAnimNotify_SetWeapon.h"
#include "Character/Player/NightPlayerCharacter.h"

void UNightAnimNotify_SetWeapon::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
  if (!MeshComp) return;
  ANightPlayerCharacter* Player = Cast<ANightPlayerCharacter>(MeshComp->GetOwner());
  if (!Player) return;

  Player->SetWeaponToPlayerHand();
}
