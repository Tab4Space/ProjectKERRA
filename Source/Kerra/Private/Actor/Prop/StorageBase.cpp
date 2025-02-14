// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Prop/StorageBase.h"

#include "Kerra/Kerra.h"

AStorageBase::AStorageBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
}

void AStorageBase::DoInteraction_Implementation(AActor* TargetActor)
{
	KERRALOG(Warning, TEXT("Do interaction"));
}

void AStorageBase::BeginPlay()
{
	Super::BeginPlay();
	
}

