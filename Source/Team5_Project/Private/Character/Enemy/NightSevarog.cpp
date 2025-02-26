// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/NightSevarog.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ANightSevarog::ANightSevarog()
{
	
	GetCharacterMovement()->bUseControllerDesiredRotation = true; // 컨트롤러의 원하는 회전을 사용하지 않음
	GetCharacterMovement()->bOrientRotationToMovement = false; // 이동 방향에 따라 캐릭터의 방향을 맞춤
	GetCharacterMovement()->RotationRate = FRotator(0.f,150.f,0.f); // 캐릭터 회전 속도 설정
	
	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(GetMesh(), TEXT("HammerCenter"));
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
