
#include "Weapon/NightWeaponRifle.h"

ANightWeaponRifle::ANightWeaponRifle()
{
	MaxBullet = 30;
	CurrentBullet = 30;
	WeaponType = "Rifle";
	Range = 2000.0f;
	Zoomtimes = 1;
}

//라이플 연사
void ANightWeaponRifle::Fire()
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
			GetWorld()->GetTimerManager().SetTimer(timer, this, &ANightWeaponRifle::Fire, 0.1f, false);
			UE_LOG(LogTemp, Error, TEXT("Ammo:%d"), CurrentBullet);
		}
	}

}

void ANightWeaponRifle::StartFire()
{
	ANightWeaponRifle::isFiring = true;
	Fire();
}

void ANightWeaponRifle::StopFire()
{
	isFiring = false;
}

void ANightWeaponRifle::Reload()
{
	CurrentBullet = MaxBullet;
}