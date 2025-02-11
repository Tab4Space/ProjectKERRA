// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StorageBase.generated.h"

UCLASS()
class KERRA_API AStorageBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AStorageBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
