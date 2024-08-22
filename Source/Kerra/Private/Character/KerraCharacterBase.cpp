// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/KerraCharacterBase.h"


AKerraCharacterBase::AKerraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;
}


void AKerraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}
