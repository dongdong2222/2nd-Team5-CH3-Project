// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/Player/NightPlayerAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Debug/DebugDrawComponent.h"
#include "Character/Player/NightPlayerCharacter.h"

void UNightPlayerAnimInstance::NativeInitializeAnimation()
{
  Super::NativeInitializeAnimation();
  AActor* Actor = GetOwningActor();
  if (!Actor) return;
  Character = Cast<ACharacter>(Actor);
  if (!Character) return;
  MovementComponent = Character->GetCharacterMovement();
}

void UNightPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
  Super::NativeUpdateAnimation(DeltaSeconds);
  UpdateRotation();
  UpdateVelocity();
  UpdateAim(DeltaSeconds);

  if (!Montage_IsPlaying(InPlaceMontage) && (DeltaRotation.Yaw >= 90.f || DeltaRotation.Yaw <= -90.f) && GroundSpeed < 10.f )
  {
    Montage_Play(InPlaceMontage);
    if (DeltaRotation.Yaw >= 90.f)
    {
      Montage_JumpToSection("right90", InPlaceMontage);
    }
    else if (DeltaRotation.Yaw <= -90.f)
    {
      Montage_JumpToSection("left90", InPlaceMontage);

    }
  }
  //if (Character)
  //{
  //  if (GroundSpeed < 10.f || !Cast<ANightPlayerCharacter>(Character)->PlayerStateTags.HasTag(FGameplayTag::RequestGameplayTag("State.Lock.Rolling")))
  //  {
  //    Character->bUseControllerRotationYaw = false;
  //  }
  //  else
  //  {
  //    Character->bUseControllerRotationYaw = true;

  //  }
  //}

}

void UNightPlayerAnimInstance::UpdateRotation()
{
  if (!Character) return;
  WorldRotation = Character->GetActorRotation();
  if (!Character->GetController()) return;
  ControllerRotation = Character->GetController()->GetControlRotation();
  DeltaRotation = UKismetMathLibrary::NormalizedDeltaRotator(ControllerRotation, WorldRotation);
  //Pitch Normalize
  double Pitch = DeltaRotation.Pitch;
  Pitch = FMath::Fmod(Pitch + 180.f, 360.f);
  if (Pitch < 0.f) Pitch += 360.f;
  Pitch -= 180.f;
  //Yaw Normalize
  double Yaw = DeltaRotation.Yaw;
  Yaw = FMath::Fmod(Yaw + 180.f, 360.f);
  if (Yaw < 0.f) Yaw += 360.f;
  Yaw -= 180.f;
  RotationForAim = FRotator(Pitch, Yaw, DeltaRotation.Roll);

}

void UNightPlayerAnimInstance::UpdateVelocity()
{
  if (!Character) return;
  WorldVelocity = MovementComponent->Velocity;
  LocalVelocity = UKismetMathLibrary::Quat_UnrotateVector(WorldRotation.Quaternion(), WorldVelocity);
  GroundSpeed = FVector(WorldVelocity.X, WorldVelocity.Y, 0.f).Length();

  WorldMoveDirection = CalculateDirection(LocalVelocity, WorldRotation);
  LocalMoveDirection = CalculateDirection(WorldVelocity, WorldRotation);

  //FVector Forward = Character->GetActorForwardVector();
  //FVector Target = LocalVelocity.GetSafeNormal2D();
  //if (FMath::IsNearlyZero(Target.Length()))
  //{
  //  LocalMoveDirection = 0;
  //}
  //else
  //{
  //  float Dot = FVector::DotProduct(Forward, Target);
  //  float angle = FMath::Acos(Dot) * (180.f / PI);
  //  FVector Cross = FVector::CrossProduct(Forward, Target);
  //  LocalMoveDirection = Cross.Z < 0? -angle: angle;
  //}
}

void UNightPlayerAnimInstance::UpdateAim(float DeltaTime)
{
  if (!Character) return;
  AController* Controller = Character->GetController();
  if (!Controller) return;
  APlayerController* PlayerController = Cast<APlayerController>(Controller);
  if (!PlayerController) return;
  FIntPoint ScreenSize = GEngine->GameViewport->Viewport->GetSizeXY();
  FVector2D ScreenCenter = { ScreenSize.X / 2.f, ScreenSize.Y / 2.f };
  FVector WorldPosition;
  FVector WorldDirection;
  UGameplayStatics::DeprojectScreenToWorld(PlayerController, ScreenCenter, WorldPosition, WorldDirection);
  ScreenCenterWorldLocation = WorldPosition;

  FHitResult HitResult;
  //FCollisionObjectQueryParams QParams(FCollisionObjectQueryParams::InitType::AllObjects);
  FVector EndPosition = WorldPosition + WorldDirection * 1000;
  GetWorld()->LineTraceSingleByChannel(
    HitResult,
    WorldPosition,
    EndPosition,
    ECC_GameTraceChannel1
  );
  //DrawDebugLine(
  //  GetWorld(),
  //  WorldPosition,
  //  EndPosition,
  //  FColor::Red,
  //  false,
  //  1.f
  //);
  USkeletalMeshComponent* Mesh = Character->GetMesh();
  FName SocketName = TEXT("WeaponSocket");
  if (Mesh && Mesh->DoesSocketExist(TEXT("WeaponSocket")))
  {
    FVector Direction;
    if (HitResult.bBlockingHit)
    {
      EndPosition = HitResult.ImpactPoint;
    }

    TargetLocation = EndPosition;
    Direction = EndPosition - Mesh->GetSocketLocation(SocketName);
    Direction.X = - Direction.X;
    //FVector OutPosition;
    //FRotator OutRotation;
    //Mesh->TransformToBoneSpace(FName(TEXT("hand_r")), FVector::ZeroVector, Direction.Rotation(), OutPosition, OutRotation);
    WorldWeaponRotation = Direction.Rotation();
    //DrawDebugLine(
    //  GetWorld(),
    //  Mesh->GetSocketLocation(SocketName),
    //  EndPosition,
    //  FColor::Blue,
    //  false,
    //  1.f
    //);
  }

    
}

void UNightPlayerAnimInstance::UpdateRolling(float DeltaTime)
{
  if (!Character) return;
  
}
