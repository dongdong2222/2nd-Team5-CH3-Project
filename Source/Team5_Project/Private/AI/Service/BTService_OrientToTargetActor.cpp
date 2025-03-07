// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BTService_OrientToTargetActor.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

UBTService_OrientToTargetActor::UBTService_OrientToTargetActor()
{
	NodeName = TEXT("Native Orient Rotation To Target Actor");

	INIT_SERVICE_NODE_NOTIFY_FLAGS();

	RotationInterpSpeed = 5.f; // 회전 보간 속도
	Interval = 0.f; // 서비스 실행 간격
	RandomDeviation = 0.f; // 실행 간격의 랜덤 편차

	// InTargetActorKey에 AActor 유형의 오브젝트 필터 추가
	InTargetActorKey.AddObjectFilter(this,GET_MEMBER_NAME_CHECKED(ThisClass,InTargetActorKey),AActor::StaticClass());
}

void UBTService_OrientToTargetActor::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	if (UBlackboardData* BBAsset = GetBlackboardAsset())
	{
		// InTargetActorKey 초기화 및 블랙보드 키 연결
		InTargetActorKey.ResolveSelectedKey(*BBAsset);
	}
}

FString UBTService_OrientToTargetActor::GetStaticDescription() const
{
	// 블랙보드 키 이름을 포함한 설명 반환
	const FString KeyDescription = InTargetActorKey.SelectedKeyName.ToString();

	return FString::Printf(TEXT("Orient rotation to %s Key %s"),*KeyDescription,*GetStaticServiceDescription());
}

void UBTService_OrientToTargetActor::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// 블랙보드에서 대상 액터 가져오기
	UObject* ActorObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(InTargetActorKey.SelectedKeyName);
	AActor* TargetActor = Cast<AActor>(ActorObject);

	// 소유 중인 Pawn 가져오기
	APawn* OwningPawn = OwnerComp.GetAIOwner()->GetPawn();

	// 소유 Pawn과 대상 액터가 유효한 경우
	if (OwningPawn && TargetActor)
	{
		// LookAt 대상 회전을 계산
		const FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(OwningPawn->GetActorLocation(),TargetActor->GetActorLocation());
		// 기존 회전과 LookAt 회전을 보간
		const FRotator TargetRot = FMath::RInterpTo(OwningPawn->GetActorRotation(),LookAtRot,DeltaSeconds,RotationInterpSpeed);

		// 소유 Pawn의 회전 설정
		OwningPawn->SetActorRotation(TargetRot);
	}
}
