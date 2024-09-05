// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_RotateToFaceTarget.generated.h"


struct FRotateToFaceTargetTaskMemory
{
	TWeakObjectPtr<APawn> OwningPawn;
	TWeakObjectPtr<AActor> TargetActor;

	bool IsValid() const
	{
		return OwningPawn.IsValid() && TargetActor.IsValid();
	}

	void Reset()
	{
		OwningPawn.Reset();
		TargetActor.Reset();
	}
};

UCLASS()
class KERRA_API UBTT_RotateToFaceTarget : public UBTTaskNode
{
	GENERATED_BODY()

	UBTT_RotateToFaceTarget();

	/* Interface */
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual uint16 GetInstanceMemorySize() const override;
	virtual FString GetStaticDescription() const override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	bool HasReacedAnglePrecision(APawn* QueryPawn, AActor* TargetActor) const;
	
	UPROPERTY(EditAnywhere, Category="FaceTarget")
	float AnglePrecision;

	UPROPERTY(EditAnywhere, Category="FaceTarget")
	float RotationInterpSpeed;

	UPROPERTY(EditAnywhere, Category="FaceTarget")
	FBlackboardKeySelector TargetToFaceKey;
	
};
