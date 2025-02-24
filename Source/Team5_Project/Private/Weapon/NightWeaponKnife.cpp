
#include "Weapon/NightWeaponKnife.h"

ANightWeaponKnife::ANightWeaponKnife()
{
	MaxBullet = 0;
	CurrentBullet = 0;
	WeaponType = "Knife";
	Range = 200.0f;
	Zoomtimes = 1;
}

//권총 단발
void ANightWeaponKnife::Fire()
{
	//delay만 추가

}