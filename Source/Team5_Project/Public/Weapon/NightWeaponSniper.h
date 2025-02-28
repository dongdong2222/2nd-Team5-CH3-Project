
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


	
	UFUNCTION(BlueprintCallable, Category = "SniperWeapon")
	void ZoomIn();
	UFUNCTION(BlueprintCallable, Category = "SniperWeapon")
	void ZoomOut();
};
