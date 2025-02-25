// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/NightPlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "Controller/Player/NightPlayerController.h"
#include "DataAsset/NightPlayerDataAsset.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "State/NightPlayerState.h"
#include "Weapon/NightWeaponBase.h"

ANightPlayerCharacter::ANightPlayerCharacter()
{
  //initialize QuickSlot
  QuickSlot.SetNum(3);


}

void ANightPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
  Super::SetupPlayerInputComponent(PlayerInputComponent);
  UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
  if (!IsValid(EnhancedInput)) return;
  ANightPlayerController* PlayerController = Cast<ANightPlayerController>(GetController());
  if (!IsValid(PlayerController)) return;

  EnhancedInput->BindAction(
    PlayerController->MoveAction,
    ETriggerEvent::Triggered,
    this,
    &ThisClass::Move
  );
  EnhancedInput->BindAction(
    PlayerController->TurnAction,
    ETriggerEvent::Triggered,
    this,
    &ThisClass::Turn
  );
  EnhancedInput->BindAction(
    PlayerController->CrouchAction,
    ETriggerEvent::Triggered,
    this,
    &ThisClass::SwitchCrouch
  );
  EnhancedInput->BindAction(
    PlayerController->RollingAction,
    ETriggerEvent::Triggered,
    this,
    &ThisClass::Rolling
  );
  EnhancedInput->BindAction(
    PlayerController->SwitchWeaponAction,
    ETriggerEvent::Triggered,
    this,
    &ThisClass::SwitchWeapon
  );
}

void ANightPlayerCharacter::Move(const FInputActionValue& Value)
{
  const FVector2D MoveInput = Value.Get<FVector2D>();
  if (!FMath::IsNearlyZero(MoveInput.X))
  {
    FVector Forward = GetController()->GetControlRotation().Vector();
    AddMovementInput(Forward, MoveInput.X);
  }
  if (!FMath::IsNearlyZero(MoveInput.Y))
  {
    FRotator Right = GetController()->GetControlRotation();
    Right.Yaw += 90.f;
    AddMovementInput(Right.Vector() , MoveInput.Y);
  }
}

void ANightPlayerCharacter::Turn(const FInputActionValue& Value)
{
  const FVector2D TurnInput = Value.Get<FVector2D>();
  AddControllerYawInput(TurnInput.X);
  AddControllerPitchInput(TurnInput.Y);
}

void ANightPlayerCharacter::SwitchCrouch(const FInputActionValue& Value)
{
  if (bIsCrouched) {
    UnCrouch();
  }
  else
  {
    Crouch();
  }
}

void ANightPlayerCharacter::StartSprint(const FInputActionValue& Value)
{
  if (auto* CharactorMovement = GetCharacterMovement())
  {
    const float SprintSpeed = Cast<UNightPlayerDataAsset>(StatData)->GetSprintSpeed();
    CharactorMovement->MaxWalkSpeed = SprintSpeed;
  }
  //FGameplayTag::RequestGameplayTag()
}

void ANightPlayerCharacter::EndSprint(const FInputActionValue& Value)
{
  if (auto* CharactorMovement = GetCharacterMovement())
  {
    const float WalkSpeed = Cast<UNightPlayerDataAsset>(StatData)->GetWalkSpeed();
    CharactorMovement->MaxWalkSpeed = WalkSpeed;
  }
}

void ANightPlayerCharacter::Rolling(const FInputActionValue& Value)
{
  //TODO : 원하는 방향으로 일정거리 구르기, 구르는 동안 타격받지 않음
  UAnimInstance* Anim = GetMesh()->GetAnimInstance();
  if (!Anim) return;
  Anim->Montage_Play(RollingMontage);
  //Anim->OnMontageEnded.AddDynamic(this, Montage);
}

void ANightPlayerCharacter::Reload(const FInputActionValue& Value)
{
  //TODO : Gun->Reload();
}

void ANightPlayerCharacter::Aim(const FInputActionValue& Value)
{
  //TODO : Gun->Aiming();
}

void ANightPlayerCharacter::Shot(const FInputActionValue& Value)
{
  //TODO : Gun->Fire();
}

void ANightPlayerCharacter::SwitchWeapon(const FInputActionValue& Value)
{
  float SwitchInput = Value.Get<float>();
  if (SwitchInput > 0) {
    AddToCurrentSlot(1);
  }
  else
  {
    AddToCurrentSlot(-1);
  }
  //TODO : AnimMontage Play로 바꾸기
  SetWeaponToPlayerHand();

}

void ANightPlayerCharacter::ESC(const FInputActionValue& Value)
{
  //TODO : ESC창 열린 후, 커서 움직이게 바뀜
}

void ANightPlayerCharacter::UsePotion(const FInputActionValue& Value)
{
  //TODO : 포션 사용
  UNightPlayerDataAsset* PlayerStatData = Cast<UNightPlayerDataAsset>(StatData);
  if (!PlayerStatData) return;
  FHealPotionData HealPotionData= PlayerStatData->GetHealPotionData();
  if (HealPotionData.Use())
  {
    PlayerStatData->SetHealth(PlayerStatData->GetHealth() + HealPotionData.HealAmount);
  }
}

void ANightPlayerCharacter::Throw(const FInputActionValue& Value)
{
  //TODO :  바로 던지는 모션 후 투척 무기 던지기
}

void ANightPlayerCharacter::Interaction(const FInputActionValue& Value)
{
  //TODO : 상호작용이 가능한 상황일때 상호작용
}


void ANightPlayerCharacter::SetFirstPersonView()
{

}

void ANightPlayerCharacter::SetThirdPersonView()
{
}

void ANightPlayerCharacter::SetWeaponToPlayerHand()
{
  ANightWeaponBase* Weapon = GetWorld()->SpawnActor<ANightWeaponBase>(
    QuickSlot[CurrentSlot],
    FVector::ZeroVector,
    FRotator::ZeroRotator
  );
  Weapon->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "WeaponSocket");
  UAnimInstance* Anim = GetMesh()->GetAnimInstance();
  if (!Anim) return;
  GetMesh()->LinkAnimClassLayers(Pistol);
}

void ANightPlayerCharacter::AddToCurrentSlot(float value)
{
  int32 Temp = CurrentSlot + value;
  if (Temp >= QuickSlot.Num())
  {
    CurrentSlot = 0;
  }
  else if (Temp < 0)
  {
    CurrentSlot = QuickSlot.Num() - 1;
  }
  else
  {
    CurrentSlot = Temp;
  }
}
