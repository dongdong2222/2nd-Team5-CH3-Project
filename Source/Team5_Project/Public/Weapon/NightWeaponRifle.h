
#pragma once

#include "CoreMinimal.h"
#include "Weapon/NightWeaponBase.h"
#include "NightWeaponRifle.generated.h"


 
UCLASS()
class TEAM5_PROJECT_API ANightWeaponRifle : public ANightWeaponBase
{
	GENERATED_BODY()
	
public:
	ANightWeaponRifle();





	void Fire()override;
	UFUNCTION(BlueprintCallable, Category = "RifleWeapon")
	void StartFire();
	UFUNCTION(BlueprintCallable, Category = "RifleWeapon")
	void StopFire();
	UFUNCTION(BlueprintCallable, Category = "RifleWeapon")
	void Reload();
};
