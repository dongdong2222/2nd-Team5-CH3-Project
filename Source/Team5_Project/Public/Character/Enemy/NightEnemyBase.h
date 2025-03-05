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
	UShapeComponent* CollisionComponent;

	// Combat
	UPROPERTY(BlueprintAssignable, Category = "Combat")
	FOnAttackEnded OnAttackEnded;

	// 적이 사망했는지 여부
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat")
	bool IsDead;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float Damage = 10.0f;
	
	ANightEnemyBase();

	// 적의 상태를 설정하는 함수
	UFUNCTION(BlueprintCallable,Category= "Night Enemy")
	void SetState(EEnemyState NewState);

	// 적이 공격 중인지 확인하는 함수
	UFUNCTION(BlueprintPure, Category = "Combat")
	bool GetIsAttacking() const;

	// 공격 몽타주가 종료되었을 때 호출되는 함수
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	// 콜리전 시작 시 호출되는 함수
	UFUNCTION()
	void OnOverlapBegin( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,int32 OtherBodyIndex, bool bFromSweep,	const FHitResult & SweepResult);

	// 콜리전 종료 시 호출되는 함수
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	// 데미지를 받을 때 호출되는 함수
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// 근접 공격을 실행하는 함수
	void MeleeAttack(FName Tag);

	// 태그를 추가하는 함수
	UFUNCTION(BlueprintCallable)
	void addTag(FName tag);

	// 태그를 제거하는 함수
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
