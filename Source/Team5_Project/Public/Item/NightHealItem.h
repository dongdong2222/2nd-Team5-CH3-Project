
#pragma once

#include "CoreMinimal.h"
#include "Item/NightBaseItem.h"
#include "NightHealItem.generated.h"


UCLASS()
class TEAM5_PROJECT_API ANightHealItem : public ANightBaseItem
{
	GENERATED_BODY()
	
public:
	ANightHealItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 HealAmount;

	virtual void ActivateItem(AActor* Activator) override;
};
