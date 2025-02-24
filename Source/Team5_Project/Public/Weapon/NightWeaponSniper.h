
#pragma once

#include "CoreMinimal.h"
#include "Weapon/NightWeaponBase.h"
#include "NightWeaponSniper.generated.h"


UCLASS()
class TEAM5_PROJECT_API ANightWeaponSniper : public ANightWeaponBase
{
	GENERATED_BODY()
	
public:
	ANightWeaponSniper();






	void Fire()override;
	UFUNCTION(BlueprintCallable, Category = "SniperWeapon")
	void Reload();
	UFUNCTION(BlueprintCallable, Category = "SniperWeapon")
	void ZoomIn();
	UFUNCTION(BlueprintCallable, Category = "SniperWeapon")
	void ZoomOut();
};
