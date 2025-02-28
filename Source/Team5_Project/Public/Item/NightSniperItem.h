#pragma once

#include "CoreMinimal.h"
#include "Item/NightWeaponItem.h"
#include "NightSniperItem.generated.h"


UCLASS()
class TEAM5_PROJECT_API ANightSniperItem : public ANightWeaponItem
{
	GENERATED_BODY()
	
public:
	ANightSniperItem();
	virtual void ActivateItem(AActor* Activator) override;
};
