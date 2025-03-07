// Fill out your copyright notice in the Description page of Project Settings.



#include "DataAsset/NightCharacterDataAsset.h"

UNightCharacterDataAsset::UNightCharacterDataAsset()
	: MaxHealth(100.f), Defence(0.f), Health(100.f)
{
}

float UNightCharacterDataAsset::GetHealth() const
{
	return Health;
}

void UNightCharacterDataAsset::SetHealth(float value)
{
	Health = FMath::Clamp(value, 0.f, MaxHealth);
}

float UNightCharacterDataAsset::GetMaxHealth() const
{
	return MaxHealth;
}

void UNightCharacterDataAsset::SetMaxHealth(float value)
{
	MaxHealth = value;
}

float UNightCharacterDataAsset::GetDefence() const
{
	return Defence;
}

void UNightCharacterDataAsset::SetDefence(float value)
{
	Defence = value;
}
