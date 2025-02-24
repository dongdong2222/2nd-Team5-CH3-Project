#pragma once

#include "CoreMinimal.h"
#include "Weapon/NightWeaponBase.h"
#include "NightWeaponPistol.generated.h"


UCLASS()
class TEAM5_PROJECT_API ANightWeaponPistol : public ANightWeaponBase
{
	GENERATED_BODY()
	
public:
	ANightWeaponPistol();




	void Fire()override;
	UFUNCTION(BlueprintCallable, Category = "PistolWeapon")
	void Reload();
};
