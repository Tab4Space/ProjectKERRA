// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Prop/StorageBase.h"

#include "KerraFunctionLibrary.h"
#include "Character/KerraHero.h"
#include "Kerra/Kerra.h"
#include "Player/KerraPlayerController.h"
#include "UI/HUD/KerraHUD.h"
#include "UI/Widget/KerraOverlayWidget.h"


AStorageBase::AStorageBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(GetRootComponent());
	
}

void AStorageBase::DoInteraction_Implementation(AActor* TargetActor)
{
	KERRALOG(Warning, TEXT("Do interaction"));

	AKerraHUD* KerraHUD = UKerraFunctionLibrary::NativeGetKerraHUD(Cast<AKerraHero>(TargetActor)->GetKerraPC());
	KerraHUD->CreateInventoryWidget();

	if(KerraHUD->GetInventoryWidget())
	{
		KerraHUD->GetOverlayWidget()->AddInventoryWindow();
	}
}

void AStorageBase::BeginPlay()
{
	Super::BeginPlay();
	
}

