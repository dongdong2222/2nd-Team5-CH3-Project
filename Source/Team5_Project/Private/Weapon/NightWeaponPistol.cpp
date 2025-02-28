#include "Weapon/NightWeaponPistol.h"

ANightWeaponPistol::ANightWeaponPistol()
{
	MaxBullet = 12;
	CurrentBullet = 12;
	WeaponType = "Pistol";
	Range = 1000.0f;
	Zoomtimes = 1;
	FireDelay = 1.0f;
}

