// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/KerraInteractInterface.h"
#include "StorageBase.generated.h"

UCLASS()
class KERRA_API AStorageBase : public AActor, public IKerraInteractInterface
{
	GENERATED_BODY()
	
public:	
	AStorageBase();
	void DoInteraction_Implementation(AActor* TargetActor) override;

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	
};
