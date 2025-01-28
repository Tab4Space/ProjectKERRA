// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/KerraCharacterBase.h"
#include "Struct/KerraQuestInfo.h"
#include "KerraNpc.generated.h"

class UKerraQuestComponent;

UCLASS()
class KERRA_API AKerraNpc : public AKerraCharacterBase
{
	GENERATED_BODY()

public:
	AKerraNpc();
	void InitForQuest();

	/* Quest Interface */
	UFUNCTION(BlueprintCallable)
	virtual void DoInteraction_Implementation(AActor* TargetActor) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void TalkDialogue(AActor* TargetActor, FKerraQuestInfo QuestInfo);

	UFUNCTION(BlueprintCallable)
	FGameplayTag FindQuestTagToGive(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void GiveQuestToPlayer(AActor* TargetActor, FGameplayTag QuestTag);

private:
	bool CanGivingQuest(FGameplayTag TagToGive, FGameplayTagContainer& TargetAcceptedQuests, FGameplayTagContainer& TargetCompletedQuest);
	

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Quest", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UKerraQuestComponent> QuestComponent = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Quest", meta=(AllowPrivateAccess="true"))
	bool bHasQuest = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Quest", meta=(AllowPrivateAccess="true", Categories="Quest.ID"))
	FGameplayTagContainer OwnedQuestTags;

	UPROPERTY(VisibleAnywhere, Category="Quest")
	TArray<FKerraQuestInfo> OwnedQuests;

	UPROPERTY(EditAnywhere, meta=(Cateroies="NPC.ID"))
	FGameplayTag NpcIDTag;
};
