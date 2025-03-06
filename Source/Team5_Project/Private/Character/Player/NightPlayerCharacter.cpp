// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/NightPlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "Controller/Player/NightPlayerController.h"
#include "DataAsset/NightPlayerDataAsset.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "State/NightPlayerState.h"
#include "Weapon/NightWeaponBase.h"
#include "DataAsset/FPlayerItemDataRow.h"
#include "MotionWarpingComponent.h"
#include "Kismet/GameplayStatics.h"
//#include "AnimInstance/Player/NightPlayerAnimInstance.h"

ANightPlayerCharacter::ANightPlayerCharacter()
{
  //initialize QuickSlot
  QuickSlot.SetNum(3);
  CurrentSlot = 0;

}


void ANightPlayerCharacter::BeginPlay()
{
  Super::BeginPlay();

  CurrentWeapon = GetWorld()->SpawnActor<ANightWeaponBase>(
    PrevWeaponClass,
    FVector::ZeroVector,
    FRotator::ZeroRotator
  );

  UAnimInstance* Anim = GetMesh()->GetAnimInstance();
  if (!Anim) return;
  Anim->OnMontageStarted.AddDynamic(this, &ANightPlayerCharacter::OnMontageStart);
  Anim->OnMontageEnded.AddDynamic(this, &ANightPlayerCharacter::OnMontageEnd);

  GetCharacterMovement()->MaxWalkSpeed  = Cast<UNightPlayerDataAsset>(StatData)->GetWalkSpeed();

  GetWorld()->GetTimerManager().SetTimer(
    SteminaTimer,
    [this]() {
      UNightPlayerDataAsset* Data = Cast<UNightPlayerDataAsset>(StatData);
      Data->SetStemina(Data->GetStemina() + 2.f);
    },
    0.5f,
    true
    );
  StatData->SetHealth(StatData->GetMaxHealth());

  UNightPlayerDataAsset* PlayerDataAsset = Cast<UNightPlayerDataAsset>(StatData);
  PlayerDataAsset->SetStemina(PlayerDataAsset->GetMaxStemina());
  
}



float ANightPlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
  //TODO : 임시 데미지 로직
  StatData->SetHealth(StatData->GetHealth() - DamageAmount);
  if (FMath::IsNearlyZero(StatData->GetHealth()))
  {
    //TODO : Updata to DamageDirection
    Dead(GetActorForwardVector());
  }
  return 0.0f;
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
    PlayerController->MoveAction,
    ETriggerEvent::Completed,
    this,
    &ThisClass::EndMove
  );
  EnhancedInput->BindAction(
    PlayerController->TurnAction,
    ETriggerEvent::Triggered,
    this,
    &ThisClass::Turn
  );
  EnhancedInput->BindAction(
    PlayerController->SprintAction,
    ETriggerEvent::Triggered,
    this,
    &ThisClass::StartSprint
  );
  EnhancedInput->BindAction(
    PlayerController->SprintAction,
    ETriggerEvent::Completed,
    this,
    &ThisClass::EndSprint
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
  EnhancedInput->BindAction(
    PlayerController->ThrowAction,
    ETriggerEvent::Triggered,
    this,
    &ThisClass::Throw
  );
  EnhancedInput->BindAction(
    PlayerController->AimAction,
    ETriggerEvent::Triggered,
    this,
    &ThisClass::Aim
  );
  EnhancedInput->BindAction(
    PlayerController->InteractionAction,
    ETriggerEvent::Triggered,
    this,
    &ThisClass::Interaction
  );
  EnhancedInput->BindAction(
    PlayerController->ReloadAction,
    ETriggerEvent::Triggered,
    this,
    &ThisClass::Reload
  );
}

void ANightPlayerCharacter::Move(const FInputActionValue& Value)
{
  if (PlayerStateTags.HasTag(FGameplayTag::RequestGameplayTag("State.Lock.Rolling"))) return;
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
  bUseControllerRotationYaw = true;
}

void ANightPlayerCharacter::EndMove(const FInputActionValue& Value)
{
  bUseControllerRotationYaw = false;
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
    PlayerStateTags.RemoveTag(FGameplayTag::RequestGameplayTag("State.UnLock.Crouch"));
    UnCrouch();
  }
  else
  {
    PlayerStateTags.AddTag(FGameplayTag::RequestGameplayTag("State.UnLock.Crouch"));
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
  if (PlayerStateTags.HasTag(FGameplayTag::RequestGameplayTag("State.Lock"))) return;
  if (PlayerStateTags.HasTag(FGameplayTag::RequestGameplayTag("State.UnLock.Crouch"))) return;
  if (Cast<UNightPlayerDataAsset>(StatData)->GetStemina() < Cast<UNightPlayerDataAsset>(StatData)->GetDashCost()) return;
  Cast<UNightPlayerDataAsset>(StatData)->SetStemina(Cast<UNightPlayerDataAsset>(StatData)->GetStemina() - Cast<UNightPlayerDataAsset>(StatData)->GetDashCost());

  UAnimInstance* Anim = GetMesh()->GetAnimInstance();
  if (!Anim) return;



  FVector TargetLocation = GetCharacterMovement()->Velocity;
  if (TargetLocation.IsNearlyZero())
  {
    TargetLocation = GetActorForwardVector();
  }
  FRotator PrevRotation = GetActorRotation();
  FRotator TargetRotation = TargetLocation.Rotation();
  TargetLocation.Normalize();
  TargetLocation = GetActorLocation() + TargetLocation * Cast<UNightPlayerDataAsset>(StatData)->GetRollingDistance();
   
  MotionWarpingComponent->AddOrUpdateWarpTargetFromLocation("RollTargetLocation", TargetLocation);
  MotionWarpingComponent->AddOrUpdateWarpTargetFromLocationAndRotation("RollTargetRotation", TargetLocation, TargetRotation);
  MotionWarpingComponent->AddOrUpdateWarpTargetFromLocationAndRotation("RollEndRotation", TargetLocation, PrevRotation);
  Anim->Montage_Play(RollingMontage, 1.3f);

  //Anim->OnMontageEnded.AddDynamic(this, Montage);
}

void ANightPlayerCharacter::Reload(const FInputActionValue& Value)
{
  if (PlayerStateTags.HasTag(FGameplayTag::RequestGameplayTag("State.Lock"))) return;
  //TODO : Gun->Reload();
  UAnimInstance* Anim = GetMesh()->GetAnimInstance();
  if (!Anim) return;
  Anim->Montage_Play(CurrentWeapon->ReloadMontage);
  K2_Reload();
}

void ANightPlayerCharacter::Aim(const FInputActionValue& Value)
{
  //TODO : Gun->Aiming();
  SetFirstPersonView();
}

void ANightPlayerCharacter::Shot(const FInputActionValue& Value)
{
  //TODO : Gun->Fire();
}

void ANightPlayerCharacter::SwitchWeapon(const FInputActionValue& Value)
{
  if (PlayerStateTags.HasTag(FGameplayTag::RequestGameplayTag("State.Lock"))) return;
  float SwitchInput = Value.Get<float>();
  if (SwitchInput > 0) {
    AddToCurrentSlot(-1);
  }
  else
  {
    AddToCurrentSlot(1);
  }
  K2_SwitchWeapon();
  //PrevWeapon = CurrentWeapon;
  //CurrentWeapon = GetWorld()->SpawnActor<ANightWeaponBase>(
  //  QuickSlot[CurrentSlot],
  //  FVector::ZeroVector,
  //  FRotator::ZeroRotator
  //);
  //CurrentWeapon->SetActorHiddenInGame(true);
  //
  //UAnimInstance* Anim = GetMesh()->GetAnimInstance();
  //if (!Anim) return;
  //Anim->Montage_Play(CurrentWeapon->EqipMontage, 1.2f);
  //Anim->LinkAnimClassLayers(CurrentWeapon->AnimLayer);
}

void ANightPlayerCharacter::ESC(const FInputActionValue& Value)
{
  //TODO : ESC창 열린 후, 커서 움직이게 바뀜
}

void ANightPlayerCharacter::UsePotion(const FInputActionValue& Value)
{
  if (PlayerStateTags.HasTag(FGameplayTag::RequestGameplayTag("State.Lock"))) return;
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
  if (PlayerStateTags.HasTag(FGameplayTag::RequestGameplayTag("State.Lock"))) return;
  //TODO :  바로 던지는 모션 후 투척 무기 던지기
  UAnimInstance* Anim = GetMesh()->GetAnimInstance();
  Anim->Montage_Play(ThrowMontage);
}



void ANightPlayerCharacter::SetThirdPersonView()
{
}

void ANightPlayerCharacter::SetWeaponToPlayerHand()
{
  UAnimInstance* Anim = GetMesh()->GetAnimInstance();
  if (!Anim) return;
  if (PrevWeapon)
  {
    PrevWeapon->Destroy();
  }

  CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "WeaponSocket");
  CurrentWeapon->SetActorHiddenInGame(false);
}

void ANightPlayerCharacter::Dead(FVector Direction)
{
  USkeletalMeshComponent* PlayerMesh = GetMesh();
  if (!PlayerMesh) return;
  //set Regdoll 
  PlayerMesh->SetCollisionProfileName(TEXT("Ragdoll"));
  PlayerMesh->SetSimulatePhysics(true);
  //Impulse
  float Impact = 4000.f;
  FVector Impulse = Direction * Impact;

  PlayerMesh->SetAllPhysicsLinearVelocity(FVector::ZeroVector);
  PlayerMesh->AddImpulseToAllBodiesBelow(Impulse);
}

FVector ANightPlayerCharacter::GetTargetLocation()
{
  FIntPoint ScreenSize = GEngine->GameViewport->Viewport->GetSizeXY();
  FVector2D ScreenCenter = { ScreenSize.X / 2.f, ScreenSize.Y / 2.f };
  FVector WorldPosition;
  FVector WorldDirection;
  APlayerController* PlayerContoller = Cast<APlayerController>(GetController());
  UGameplayStatics::DeprojectScreenToWorld(PlayerContoller, ScreenCenter, WorldPosition, WorldDirection);
  FVector EndPosition = WorldPosition + WorldDirection * 1000;
  return EndPosition;
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

void ANightPlayerCharacter::OnMontageStart(UAnimMontage* Montage)
{
  if (Montage == RollingMontage)
  {
    PlayerStateTags.AddTag(FGameplayTag::RequestGameplayTag("State.Lock.Rolling"));
    bUseControllerRotationYaw = false;

  }
  else if (Montage == ThrowMontage)
  {
    PlayerStateTags.AddTag(FGameplayTag::RequestGameplayTag("State.Lock.Throw"));
  }
  else if (Montage == CurrentWeapon->EqipMontage)
  {
    PlayerStateTags.AddTag(FGameplayTag::RequestGameplayTag("State.Lock.Equip"));
  }
  else if (Montage == CurrentWeapon->ReloadMontage)
  {
    PlayerStateTags.AddTag(FGameplayTag::RequestGameplayTag("State.Lock.Reload"));
  }
}

void ANightPlayerCharacter::OnMontageEnd(UAnimMontage* Montage, bool bInterrupted)
{
  if (Montage == RollingMontage)
  {
    PlayerStateTags.RemoveTag(FGameplayTag::RequestGameplayTag("State.Lock.Rolling"));
    bUseControllerRotationYaw = false;
  }
  else if (Montage == ThrowMontage)
  {
    PlayerStateTags.RemoveTag(FGameplayTag::RequestGameplayTag("State.Lock.Throw"));
  }
  else if (Montage == CurrentWeapon->EqipMontage)
  {
    PlayerStateTags.RemoveTag(FGameplayTag::RequestGameplayTag("State.Lock.Equip"));
  }
  else if (Montage == CurrentWeapon->ReloadMontage)
  {
    PlayerStateTags.RemoveTag(FGameplayTag::RequestGameplayTag("State.Lock.Reload"));
  }
}
