#include "Weapon/NightWeaponBase.h"

ANightWeaponBase::ANightWeaponBase()
{
    PrimaryActorTick.bCanEverTick = false;

    Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
    SetRootComponent(Scene);



    SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
    SkeletalMesh->SetupAttachment(Scene);
}


FName ANightWeaponBase::GetWeaponType() const
{
    return WeaponType;
}

void ANightWeaponBase::DestroyWeapon()
{
    Destroy();
}

void ANightWeaponBase::Fire()
{
	if (CurrentBullet == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No Ammo"));
	}

	if (CurrentBullet != 0)
	{
		if (isFiring)
		{
			CurrentBullet--;
			GetWorld()->GetTimerManager().SetTimer(timer, this, &ANightWeaponBase::Fire, FireDelay, false);
			UE_LOG(LogTemp, Error, TEXT("Ammo:%d"), CurrentBullet);
		}
	}

}

void ANightWeaponBase::StartFire()
{
	ANightWeaponBase::isFiring = true;
	Fire();
}

void ANightWeaponBase::StopFire()
{
	isFiring = false;
}

void ANightWeaponBase::Reload()
{
	CurrentBullet = MaxBullet;
}