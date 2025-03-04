// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/NightSevarog.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ANightSevarog::ANightSevarog()
{
	
	GetCharacterMovement()->bUseControllerDesiredRotation = true; 
	GetCharacterMovement()->bOrientRotationToMovement = false; 
	GetCharacterMovement()->RotationRate = FRotator(0.f,150.f,0.f); // 캐릭터 회전 속도 설정
	
	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(GetMesh(), TEXT("HammerCenter"));
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ANightSevarog::Fire_SoulSiphon()
{
    FVector ActorLocation = GetActorLocation();
    FVector ForwardVector = GetActorForwardVector();
    FVector LocationOffset = ForwardVector * 150.0f;
    FVector SpawnLocation = ActorLocation + LocationOffset;
    FRotator ActorRotation = GetActorRotation();

    UParticleSystemComponent* ParticleComponent = UGameplayStatics::SpawnEmitterAtLocation(
        GetWorld(),
        GhostHandParticleSystem,
        SpawnLocation,
        ActorRotation,
        FVector(1.25f, 1.25f, 1.25f),
        true,
        EPSCPoolMethod::None,
        true
    );

    if (ParticleComponent != nullptr)
    {
        FVector EndLocationOffset = ForwardVector * 500.0f;
        FVector TraceEndLocation = ActorLocation + EndLocationOffset;
        FHitResult HitResult;

        TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
        ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn)); // 플레이어 캐릭터 추적

        bool bHit = UKismetSystemLibrary::SphereTraceSingleForObjects(
            GetWorld(),
            SpawnLocation,
            TraceEndLocation,
            300.0f,
            ObjectTypes,
            false,
            TArray<AActor*>(),
            EDrawDebugTrace::None,
            HitResult,
            true,
            FLinearColor::Red,
            FLinearColor::Green,
            5.0f
        );

        if (bHit && HitResult.GetActor())
        {
            // 데미지를 줄 액터 가져오기
            AActor* HitActor = HitResult.GetActor();

            // HitActor가 ACharacter인지 확인 (필요한 경우)
            ACharacter* HitCharacter = Cast<ACharacter>(HitActor);
            if (HitCharacter)
            {
                // 데미지 가하기
                UGameplayStatics::ApplyPointDamage(
                    HitCharacter,      // 데미지를 받을 액터
                    Damage,        // 데미지 양 (헤더에 float DamageAmount; 로 선언하고 값을 설정해야 함)
                    (TraceEndLocation - SpawnLocation).GetSafeNormal(), // 데미지 방향 (시작점에서 끝점 방향)
                    HitResult,         // Hit Result
                    nullptr,           // 데미지를 가한 컨트롤러 (nullptr 가능)
                    this,              // 데미지를 가한 액터 (Sevarog)
                    UDamageType::StaticClass() // 데미지 유형 클래스 (C++에서 생성하거나 Blueprint에서 참조)
                );
            }
        }
    }
}
