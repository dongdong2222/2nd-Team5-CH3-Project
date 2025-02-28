#pragma once

#include "CoreMinimal.h"
#include "Item/NightWeaponItem.h"
#include "NightPistolItem.generated.h"


UCLASS()
class TEAM5_PROJECT_API ANightPistolItem : public ANightWeaponItem
{
	GENERATED_BODY()
	
public:
	ANightPistolItem();
	virtual void ActivateItem(AActor* Activator) override;
};
