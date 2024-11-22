// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Area/KerraAreaBase.h"

#include "Component/Quest/KerraQuestComponent.h"
#include "Components/BoxComponent.h"
#include "Interface/KerraQuestInterface.h"


AKerraAreaBase::AKerraAreaBase()
{
	PrimaryActorTick.bCanEverTick = false;

	AreaCollision = CreateDefaultSubobject<UBoxComponent>("AreaCollision");
	SetRootComponent(AreaCollision);
	AreaCollision->OnComponentBeginOverlap.AddUniqueDynamic(this, &AKerraAreaBase::OnBoxCollisionBeginOverlap);

}

void AKerraAreaBase::OnBoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if(IKerraQuestInterface* QuestInterface = Cast<IKerraQuestInterface>(OtherActor))
	{
		// QuestInterface->GetQuestComponent()->AddQuest()
	}
}
