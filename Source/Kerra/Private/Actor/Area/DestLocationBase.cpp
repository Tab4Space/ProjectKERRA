// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Area/DestLocationBase.h"

#include "Component/Quest/KerraQuestComponent.h"
#include "Interface/KerraQuestInterface.h"

void ADestLocationBase::OnBoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                                   bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("On Overlap"));
	if(IKerraQuestInterface* QuestInterface = Cast<IKerraQuestInterface>(OtherActor))
	{
		UKerraQuestComponent* QuestComponent = QuestInterface->GetQuestComponent();
		QuestComponent->AddItemToQuestObjective(EQuestItemName::None, ENpcName::None, AreaName);
	}
	
}