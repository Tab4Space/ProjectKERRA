// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Item/Pickup/KerraPickUpBase.h"
#include "Interface/KerraInteractInterface.h"
#include "Struct/KerraQuestData.h"
#include "KerraCollectableBase.generated.h"

/**
 * 
 */
UCLASS()
class KERRA_API AKerraCollectableBase : public AKerraPickUpBase, public IKerraInteractInterface
{
	GENERATED_BODY()

public:
	AKerraCollectableBase();

	/* Quest Interface */
	UFUNCTION(BlueprintCallable)
	virtual void DoInteraction_Implementation(AActor* TargetActor) override;

private:
	// Unique tag for item
	UPROPERTY(EditAnywhere, Category="Quest", meta=(AllowPrivateAccess="true", Categories="Item.ID"))
	FGameplayTag ItemIDTag;
	
	UPROPERTY(EditAnywhere, Category="Quest", meta=(AllowPrivateAccess="true"))
	bool bUseInQuest;

	UPROPERTY(EditAnywhere, Category="Quest", meta=(AllowPrivateAccess="true", EditCondition="bUseInQuest", Categories="Quest.ID", EditConditionHides))
	FGameplayTagContainer AppliedQuests;

};
