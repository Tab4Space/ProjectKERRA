// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Item/Pickup/KerraPickUpBase.h"

#include "Components/SphereComponent.h"


AKerraPickUpBase::AKerraPickUpBase()
{
	PrimaryActorTick.bCanEverTick = false;

	PickUpCollsion = CreateDefaultSubobject<USphereComponent>("PickUpCollision");
	SetRootComponent(PickUpCollsion);
	PickUpCollsion->InitSphereRadius(50.f);
	PickUpCollsion->OnComponentBeginOverlap.AddUniqueDynamic(this, &AKerraPickUpBase::OnPickUpCollisionBeginOverlap);
	
}

void AKerraPickUpBase::OnPickUpCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

