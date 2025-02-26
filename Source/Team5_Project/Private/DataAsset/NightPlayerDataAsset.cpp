// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/NightPlayerDataAsset.h"

float UNightPlayerDataAsset::GetStemina() const
{
  return Stemina;
}

void UNightPlayerDataAsset::SetStemina(float value)
{
  Stemina = FMath::Clamp(value, 0.f, MaxStemina);
}

float UNightPlayerDataAsset::GetMaxStemina() const
{
  return MaxStemina;
}

void UNightPlayerDataAsset::SetMaxStemina(float value)
{
  MaxStemina = value;
}

float UNightPlayerDataAsset::GetWalkSpeed() const
{
  return WalkSpeed;
}

void UNightPlayerDataAsset::SetWalkSpeed(float value)
{
  WalkSpeed = value;
}

float UNightPlayerDataAsset::GetSprintSpeed() const
{
  return SprintSpeed;
}

void UNightPlayerDataAsset::SetSprintSpeed(float value)
{
  SprintSpeed = value;
}

float UNightPlayerDataAsset::GetDashCost() const
{
  return DashCost;
}

void UNightPlayerDataAsset::SetDashCost(float value)
{
  DashCost = value;
}

FHealPotionData UNightPlayerDataAsset::GetHealPotionData() const
{
  return HealPotionData;
}

void UNightPlayerDataAsset::SetHealPotionData(FHealPotionData value)
{
  HealPotionData = value;
}

float UNightPlayerDataAsset::GetRollingDistance() const
{
    return RollingDistance;
}

void UNightPlayerDataAsset::SetRollingDistance(float value)
{
  RollingDistance = value;
}
