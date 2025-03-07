#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "NightWeaponInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UNightWeaponInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TEAM5_PROJECT_API INightWeaponInterface
{
	GENERATED_BODY()

	
public:

	virtual FName GetWeaponType()const = 0;
};
