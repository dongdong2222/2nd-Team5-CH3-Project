#include "Item/NightHealItem.h"
#include "Character/Player/NightPlayerCharacter.h"


ANightHealItem::ANightHealItem()
{
    HealAmount = 3.0f;
    ItemType = "Healing";
}

void ANightHealItem::ActivateItem(AActor* Activator)
{
    if (Activator && Activator->ActorHasTag("Player"))
    {

        if (ANightPlayerCharacter* PlayerCharacter = Cast<ANightPlayerCharacter>(Activator))
        {
            //PlayerCharacter->AddHealth(HealAmount);
        }
        DestroyItem();
    }
}