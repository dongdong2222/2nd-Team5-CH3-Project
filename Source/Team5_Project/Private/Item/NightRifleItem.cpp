#include "Item/NightRifleItem.h"

ANightRifleItem::ANightRifleItem()
{
	
	ItemType = "Rifle";
}

void ANightRifleItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
}