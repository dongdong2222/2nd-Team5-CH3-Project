// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/NightCharacterBase.h"
#include "NightEnemyBase.generated.h"

class UBoxComponent;

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle        UMETA(DisplayName = "Idle"),
	Moving      UMETA(DisplayName = "Moving"),
	Combat		UMETA(DisplayName = "Combat"),
	Resting     UMETA(DisplayName = "Resting"),
	Dead        UMETA(DisplayName = "Dead")
};


USTRUCT(BlueprintType)
struct FTagAnimation
{
	GENERATED_BODY()
	// 태그
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TagAnimation")
	FName Tag;
	// 애니메이션 몽타주
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TagAnimation")
	UAnimMontage* AnimationMontage;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackEnded);

UCLASS()
class TEAM5_PROJECT_API ANightEnemyBase : public ANightCharacterBase
{
	GENERATED_BODY()
	
public:
	// Animation Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TArray<FTagAnimation> TagAnimations;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* DamageMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* DeathMontage;

	// State
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	EEnemyState EnemyState;

	// Collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	UBoxComponent* CollisionBox;

	// Combat
	UPROPERTY(BlueprintAssignable, Category = "Combat")
	FOnAttackEnded OnAttackEnded;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float Damage = 10.0f;
	
	ANightEnemyBase();

	UFUNCTION(BlueprintCallable,Category= "Night Enemy")
	void SetState(EEnemyState NewState);

	UFUNCTION(BlueprintPure, Category = "Combat")
	bool GetIsAttacking() const;

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
	void OnOverlapBegin( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,int32 OtherBodyIndex, bool bFromSweep,	const FHitResult & SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
	void MeleeAttack(FName Tag);

	UFUNCTION(BlueprintCallable)
	void addTag(FName tag);

	UFUNCTION(BlueprintCallable)
	void removeTag(FName tag);

protected:
	UFUNCTION()
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
private:
	bool bIsAttacking;
	bool bAlreadyDamaged;
	
};
