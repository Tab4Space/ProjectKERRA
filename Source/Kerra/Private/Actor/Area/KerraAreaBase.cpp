// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Area/KerraAreaBase.h"

#include "Components/BoxComponent.h"


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
	
}
