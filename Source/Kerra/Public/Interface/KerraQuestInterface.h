// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "KerraQuestInterface.generated.h"

class UKerraQuestComponent;

UINTERFACE(MinimalAPI)
class UKerraQuestInterface : public UInterface
{
	GENERATED_BODY()
};


class KERRA_API IKerraQuestInterface
{
	GENERATED_BODY()

public:
	virtual UKerraQuestComponent* GetQuestComponent() const;

	UFUNCTION()
	virtual void DoInteraction(AActor* TargetActor);
};
