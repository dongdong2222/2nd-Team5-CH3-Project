
#pragma once

#include "CoreMinimal.h"
#include "Weapon/NightWeaponBase.h"
#include "NightWeaponKnife.generated.h"


UCLASS()
class TEAM5_PROJECT_API ANightWeaponKnife : public ANightWeaponBase
{
	GENERATED_BODY()
	
public:
	ANightWeaponKnife();

	void Fire()override;
};
