
#include "Weapon/NightWeaponSniper.h"


ANightWeaponSniper::ANightWeaponSniper()
{
	MaxBullet = 5;
	CurrentBullet = 5;
	WeaponType = "Sniper";
	Range = 5000.0f;
	Zoomtimes = 3;
	FireDelay = 2.0f;
}


void ANightWeaponSniper::ZoomIn()
{
	//캐릭터의 카메라 컴포넌트의 transform 값 이용
}

void ANightWeaponSniper::ZoomOut()
{
	//캐릭터의 카메라 컴포넌트의 transform 값 이용
}