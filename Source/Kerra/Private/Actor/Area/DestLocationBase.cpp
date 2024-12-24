// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Area/DestLocationBase.h"

#include "Component/Quest/KerraQuestComponent.h"
#include "Interface/KerraQuestInterface.h"

ADestLocationBase::ADestLocationBase()
{
}

void ADestLocationBase::DoInteraction_Implementation(AActor* TargetActor)
{
	
}

void ADestLocationBase::OnBoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("On Overlap"));
	
	if(!bUseInQuest || AppliedQuests.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("This Location is not for quest or not in used quest"));
		return;
	}
	
	if(IKerraQuestInterface* QuestInterface = Cast<IKerraQuestInterface>(OtherActor))
	{
		UKerraQuestComponent* TargetQuestComponent = QuestInterface->GetKerraQuestComponent();
		const FGameplayTagContainer TargetAcceptedQuests = TargetQuestComponent->GetAcceptedQuestTags();

		for(FGameplayTag QuestTagToClear : TargetAcceptedQuests.GetGameplayTagArray())
		{
			if(AppliedQuests.HasTagExact(QuestTagToClear))
			{
				TargetQuestComponent->ClearQuest(QuestTagToClear);
				break;
			}
		}
	}
	
}
