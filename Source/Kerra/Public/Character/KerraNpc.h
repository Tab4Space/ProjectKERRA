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
	virtual void DoInteraction(AActor* TargetActor) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void GiveQuestToPlayer(AActor* TargetActor);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Quest", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UKerraQuestComponent> QuestComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Quest", meta=(AllowPrivateAccess="true"))
	bool bHasQuest = false;

	UPROPERTY(VisibleAnywhere, Category="Quest")
	TArray<FKerraQuestInfo> OwnedQuest;

	UPROPERTY(EditAnywhere, Category="Quest")
	EQuestGiver NpcName = EQuestGiver::None;
};
