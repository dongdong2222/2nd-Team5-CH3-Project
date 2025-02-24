#include "Weapon/NightWeaponBase.h"

ANightWeaponBase::ANightWeaponBase()
{
    PrimaryActorTick.bCanEverTick = false;

    Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
    SetRootComponent(Scene);



    SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
    SkeletalMesh->SetupAttachment(Scene);
}


FName ANightWeaponBase::GetWeaponType() const
{
    return WeaponType;
}

void ANightWeaponBase::DestroyWeapon()
{
    Destroy();
}

void ANightWeaponBase::Fire()
{

}