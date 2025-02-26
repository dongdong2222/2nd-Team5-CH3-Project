
#pragma once

#include "CoreMinimal.h"
#include "Item/NightWeaponItem.h"
#include "NightRifleItem.generated.h"


UCLASS()
class TEAM5_PROJECT_API ANightRifleItem : public ANightWeaponItem
{
	GENERATED_BODY()
	
public:
	ANightRifleItem();
	virtual void ActivateItem(AActor* Activator) override;
};
