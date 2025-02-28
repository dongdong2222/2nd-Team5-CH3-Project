
#pragma once

#include "CoreMinimal.h"
#include "Item/NightBaseItem.h"
#include "NightWeaponItem.generated.h"


UCLASS()
class TEAM5_PROJECT_API ANightWeaponItem : public ANightBaseItem
{
	GENERATED_BODY()
	
public:
	ANightWeaponItem();

protected:
	virtual void ActivateItem(AActor* Activator) override;
};
