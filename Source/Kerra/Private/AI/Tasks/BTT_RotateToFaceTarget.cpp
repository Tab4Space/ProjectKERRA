// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTT_RotateToFaceTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"


UBTT_RotateToFaceTarget::UBTT_RotateToFaceTarget()
{
	NodeName = TEXT("Native Rotate to Face Target Actor");
	AnglePrecision = 10.f;
	RotationInterpSpeed = 5.f;

	bNotifyTick = true;
	bNotifyTaskFinished = true;
	bCreateNodeInstance = false;

	INIT_TASK_NODE_NOTIFY_FLAGS();
	TargetToFaceKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(ThisClass, TargetToFaceKey), AActor::StaticClass());
}

void UBTT_RotateToFaceTarget::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	if(UBlackboardData* BBAsset = GetBlackboardAsset())
	{
		// Find ID and class of selected key
		TargetToFaceKey.ResolveSelectedKey(*BBAsset);
	}
}

uint16 UBTT_RotateToFaceTarget::GetInstanceMemorySize() const
{
	// 구조체에 연속적인 메모리 블록 할당, 이후 구조체에서 필요한 값을 검색할 수 있다
	return sizeof(FRotateToFaceTargetTaskMemory);
}

FString UBTT_RotateToFaceTarget::GetStaticDescription() const
{
	const FString KeyDescription = TargetToFaceKey.SelectedKeyName.ToString();
	return FString::Printf(TEXT("Smoothly rotates to face %s key until the angle precesion %s is reached"), *KeyDescription, *FString::SanitizeFloat(AnglePrecision));
}

EBTNodeResult::Type UBTT_RotateToFaceTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UObject* ActorObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("TargetActor"));
	AActor* TargetActor = Cast<AActor>(ActorObject);

	APawn* OwningPawn = OwnerComp.GetAIOwner()->GetPawn();

	FRotateToFaceTargetTaskMemory* Memory = CastInstanceNodeMemory<FRotateToFaceTargetTaskMemory>(NodeMemory);
	check(Memory);

	Memory->OwningPawn = OwningPawn;
	Memory->TargetActor = TargetActor;

	if(!Memory->IsValid())
	{
		return EBTNodeResult::Failed;
	}

	if(HasReacedAnglePrecision(OwningPawn, TargetActor))
	{
		Memory->Reset();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::InProgress;
}

void UBTT_RotateToFaceTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FRotateToFaceTargetTaskMemory* Memory = CastInstanceNodeMemory<FRotateToFaceTargetTaskMemory>(NodeMemory);
	
	if(!Memory->IsValid())
	{
		// Done task in tick
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	if(HasReacedAnglePrecision(Memory->OwningPawn.Get(), Memory->TargetActor.Get()))
	{
		Memory->Reset();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else
	{
		const FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(Memory->OwningPawn->GetActorLocation(), Memory->TargetActor->GetActorLocation());
		const FRotator TargetRot = FMath::RInterpTo(Memory->OwningPawn->GetActorRotation(), LookAtRot, DeltaSeconds, RotationInterpSpeed);
		Memory->OwningPawn->SetActorRotation(TargetRot);
	}
}

bool UBTT_RotateToFaceTarget::HasReacedAnglePrecision(APawn* QueryPawn, AActor* TargetActor) const
{
	// 쿼리 지점에서 대상 액터를 가리키는 normal vector 얻기
	const FVector OwenrForward = QueryPawn->GetActorForwardVector();
	const FVector OwnerToTargetNormalized = (TargetActor->GetActorLocation() - QueryPawn->GetActorLocation()).GetSafeNormal();

	// 벡터를 각도로 
	const float DotResult = FVector::DotProduct(OwenrForward, OwnerToTargetNormalized);
	const float AngleDiff = UKismetMathLibrary::DegAcos(DotResult);
	
	return AngleDiff <= AnglePrecision;
}
