#include "Item/NightSniperItem.h"

ANightSniperItem::ANightSniperItem()
{

	ItemType = "Sniper";
}

void ANightSniperItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
}