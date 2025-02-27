
#include "Weapon/NightWeaponRifle.h"

ANightWeaponRifle::ANightWeaponRifle()
{
	MaxBullet = 30;
	CurrentBullet = 30;
	WeaponType = "Rifle";
	Range = 2000.0f;
	Zoomtimes = 1;
	FireDelay = 0.2f;
}

