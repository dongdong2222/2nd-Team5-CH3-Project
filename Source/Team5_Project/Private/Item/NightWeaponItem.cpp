#include "Item/NightWeaponItem.h"

ANightWeaponItem::ANightWeaponItem()
{
   
    
    ItemType = "DefaultWeapon";
}

void ANightWeaponItem::ActivateItem(AActor* Activator)
{
    // 플레이어 태그 확인
    if (Activator && Activator->ActorHasTag("Player"))
    {
        //디버그 메시지
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Player gained Weapon!")));

    
        DestroyItem();
    }
}