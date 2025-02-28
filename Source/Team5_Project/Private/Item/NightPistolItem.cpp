#include "Item/NightPistolItem.h"

ANightPistolItem::ANightPistolItem()
{

	ItemType = "Pistol";
}

void ANightPistolItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
}