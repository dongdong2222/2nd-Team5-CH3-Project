
#include "Weapon/NightWeaponSniper.h"


ANightWeaponSniper::ANightWeaponSniper()
{
	MaxBullet = 5;
	CurrentBullet = 5;
	WeaponType = "Sniper";
	Range = 5000.0f;
	Zoomtimes = 3;
}

//스나이퍼 단발
void ANightWeaponSniper::Fire()
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
	//delay 추가?
}


void ANightWeaponSniper::Reload()
{
	CurrentBullet = MaxBullet;
}

void ANightWeaponSniper::ZoomIn()
{
	//캐릭터의 카메라 컴포넌트의 transform 값 이용
}

void ANightWeaponSniper::ZoomOut()
{
	//캐릭터의 카메라 컴포넌트의 transform 값 이용
}