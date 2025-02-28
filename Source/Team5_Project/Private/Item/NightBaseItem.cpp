
#include "Item/NightBaseItem.h"
#include "Components/SphereComponent.h"

ANightBaseItem::ANightBaseItem()
{
 	
	PrimaryActorTick.bCanEverTick = false;


    Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
    SetRootComponent(Scene);

    Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
    Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    Collision->SetupAttachment(Scene);

    SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
    SkeletalMesh->SetupAttachment(Collision);

    
    Collision->OnComponentBeginOverlap.AddDynamic(this, &ANightBaseItem::OnItemOverlap);
    Collision->OnComponentEndOverlap.AddDynamic(this, &ANightBaseItem::OnItemEndOverlap);
}

void ANightBaseItem::OnItemOverlap(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodeyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor->ActorHasTag("Player"))
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Overlap!!!")));
        ActivateItem(OtherActor);
    }
}
void ANightBaseItem::OnItemEndOverlap(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodeyIndex)
{

}
void ANightBaseItem::ActivateItem(AActor* ActiveActor)
{
    //테스트용 디버그 메시지
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Overlap!!")));
}
FName ANightBaseItem::GetItemType() const
{
    return ItemType;
}

void ANightBaseItem::DestroyItem()
{
    Destroy();
}
