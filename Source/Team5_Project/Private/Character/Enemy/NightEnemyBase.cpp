// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/NightEnemyBase.h"

#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Controller/Enemy/NightAIController.h"
#include "DataAsset/NightCharacterDataAsset.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ANightEnemyBase::ANightEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = ANightAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned; // AI가 월드에 배치되거나 스폰될 때 자동으로 제어
	bUseControllerRotationPitch = false; // Pitch 회전을 컨트롤러로 사용하지 않음
	bUseControllerRotationRoll = false; // Roll 회전을 컨트롤러로 사용하지 않음
	bUseControllerRotationYaw = false; // Yaw 회전을 컨트롤러로 사용하지 않음
	
	GetCharacterMovement()->bUseControllerDesiredRotation = false; // 컨트롤러의 원하는 회전을 사용하지 않음
	GetCharacterMovement()->bOrientRotationToMovement = true; // 이동 방향에 따라 캐릭터의 방향을 맞춤
	GetCharacterMovement()->RotationRate = FRotator(0.f,180.f,0.f); // 캐릭터 회전 속도 설정
	GetCharacterMovement()->MaxWalkSpeed = 300.f; // 캐릭터의 최대 이동 속도(걷기) 설정
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f; // 걷는 도중 제동 감속 설정
	
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore); // CapsuleComponent에서 Camera 채널 무시
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore); // Mesh에서 Camera 채널 무시
	
	EnemyState = EEnemyState::Idle;
	
}

void ANightEnemyBase::SetState(EEnemyState NewState)
{
	EnemyState = NewState;
}

bool ANightEnemyBase::GetIsAttacking() const
{
	return bIsAttacking;
}

void ANightEnemyBase::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	bIsAttacking = false; // 공격 상태를 비활성화
	OnAttackEnded.Broadcast(); // 공격 종료 이벤트를 브로드캐스트
}

void ANightEnemyBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(bAlreadyDamaged)
	{
		return;
	}
	
	// 유효한 액터 체크 및 자기 자신 제외
	if (!OtherActor || OtherActor == this)
	{
		return;
	}

	// 오버랩한 액터가 Pawn인지 확인
	APawn* OtherPawn = Cast<APawn>(OtherActor);
	if (!OtherPawn)
	{
		return;
	}

	// 오버랩한 Pawn의 컨트롤러에서 팀 정보 얻기
	AController* OtherController = OtherPawn->GetController();
	IGenericTeamAgentInterface* OtherTeamAgent = OtherController ? Cast<IGenericTeamAgentInterface>(OtherController) : nullptr;
	if (!OtherTeamAgent)
	{
		return;
	}

	

	// 자신의 소유(Pawn)가 있다면, 그 Pawn의 컨트롤러에서 팀 정보 얻기
	AController* MyController = nullptr;
	if (AController* OwnerController = Cast<AController>(GetOwner()))
	{
		MyController = OwnerController;
	}
	else if (APawn* MyPawn = Cast<APawn>(GetOwner()))
	{
		MyController = MyPawn->GetController();
	}

	IGenericTeamAgentInterface* MyTeamAgent = MyController ? Cast<IGenericTeamAgentInterface>(MyController) : nullptr;

	// 팀 정보 비교: 서로 다른 팀일 경우 데미지 적용
	// 여기서는 GetGenericTeamId()를 사용하여 팀 비교
	if (MyTeamAgent->GetGenericTeamId() != OtherTeamAgent->GetGenericTeamId())
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyController, this, nullptr);
		bAlreadyDamaged = true;
	}
	
}

void ANightEnemyBase::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bAlreadyDamaged = false;
}

float ANightEnemyBase::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
                                  class AController* EventInstigator, AActor* DamageCauser)
{
	// 기본 피해 처리
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if(ActualDamage <= 0.f)
	{
		return 0.f;
	}

	UAnimInstance* AnimIns = GetMesh()->GetAnimInstance();
	if (!AnimIns)
	{
		return ActualDamage;
	}

	if (IsDead)
	{
		return ActualDamage;
	}

	// 체력 차감
	Health -= ActualDamage;
	
	// 체력이 0 이하라면 DeathMontage 재생
	if (Health <= 0.f)
	{
		IsDead = true;
		
		if(DeathMontage)
		{
			AnimIns->Montage_Play(DeathMontage, 1.f);
		}

		if (AAIController* AIController = Cast<AAIController>(GetController()))
		{
			AIController->GetBlackboardComponent()->SetValueAsEnum(FName("State"),static_cast<uint8>(EEnemyState ::Dead));
				
			if (AIController->BrainComponent)
			{
				AIController->BrainComponent->StopLogic(TEXT("Enemy is dead"));
			}
		}
		// 캐릭터의 콜리전 비활성화 
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
	}
	// 체력이 남아있다면 피해 몽타주 재생 
	else
	{
		if(DamageMontage)
		{
			AnimIns->Montage_Play(DamageMontage, 1.f);
		}
	}

	return ActualDamage;
}

void ANightEnemyBase::MeleeAttack(FName Tag)
{
	if (bIsAttacking)
	{
		return;
	}

	UAnimMontage* AttackMontage = nullptr;
	for (const FTagAnimation& TagAnim : TagAnimations)
	{
		if (TagAnim.Tag == Tag)
		{
			AttackMontage = TagAnim.AnimationMontage;
			break;
		}
	}

	checkf(AttackMontage, TEXT("AttackMontage is null at %s"), *GetName())
	if (AttackMontage)
	{
		UAnimInstance* AnimIns = GetMesh()->GetAnimInstance(); // 캐릭터의 메쉬에서 애니메이션 인스턴스를 가져옴
		float MontageDuration = AnimIns->Montage_Play(AttackMontage, 1.f); // 지정된 몽타주를 재생하고 그 재생 시간을 반환
		if (MontageDuration > 0.f) // 몽타주가 유효하고 재생 시간이 0보다 클 경우
		{
			bIsAttacking = true; // 공격 상태를 활성화

			FOnMontageEnded MontageEndedDelegate; // 몽타주의 끝 이벤트 등록을 위한 델리게이트 생성
			MontageEndedDelegate.BindUObject(this, &ANightEnemyBase::OnAttackMontageEnded); // 델리게이트에 OnAttackMontageEnded 함수 바인딩
			AnimIns->Montage_SetEndDelegate(MontageEndedDelegate, AttackMontage); // 몽타주 끝 이벤트에 델리게이트 설정
		}
		
	}
}

void ANightEnemyBase::addTag(FName tag)
{
	Tags.AddUnique(tag);
}

void ANightEnemyBase::removeTag(FName tag)
{
	Tags.Remove(tag);
}

void ANightEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	if (CollisionComponent)
	{
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ANightEnemyBase::OnOverlapBegin);
		CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ANightEnemyBase::OnEndOverlap);	
	}

	/*if (StatData)
	{
		StatData->GetMaxHealth();
	}*/
	
}

void ANightEnemyBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}


