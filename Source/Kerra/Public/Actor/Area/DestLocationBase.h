// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Area/KerraAreaBase.h"
#include "Interface/KerraInteractInterface.h"
#include "Struct/KerraQuestInfo.h"
#include "DestLocationBase.generated.h"


UCLASS()
class KERRA_API ADestLocationBase : public AKerraAreaBase, public IKerraInteractInterface
{
	GENERATED_BODY()

public:
	ADestLocationBase();

	virtual void DoInteraction_Implementation(AActor* TargetActor) override;

protected:
	virtual void OnBoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true", Categories="Location.ID"))
	FGameplayTag LocationIDTag;

	UPROPERTY(EditAnywhere, Category="Quest", meta=(AllowPrivateAccess="true"))
	bool bUseInQuest;

	UPROPERTY(EditAnywhere, Category="Quest", meta=(AllowPrivateAccess="true", EditCondition="bUseInQuest", Categories="Quest.ID", EditConditionHides))
	FGameplayTagContainer AppliedQuests;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	bool bHasQuest;
};
