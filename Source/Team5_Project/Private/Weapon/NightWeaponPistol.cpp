#include "Weapon/NightWeaponPistol.h"

ANightWeaponPistol::ANightWeaponPistol()
{
	MaxBullet = 12;
	CurrentBullet = 12;
	WeaponType = "Pistol";
	Range = 1000.0f;
	Zoomtimes = 1;
}

//권총 단발
void ANightWeaponPistol::Fire()
{
	if (CurrentBullet == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No Ammo"));
	}

	if (CurrentBullet != 0)
	{
		CurrentBullet--;
		UE_LOG(LogTemp, Error, TEXT("Ammo:%d"), CurrentBullet);
	}

}


void ANightWeaponPistol::Reload()
{
	CurrentBullet = MaxBullet;
}