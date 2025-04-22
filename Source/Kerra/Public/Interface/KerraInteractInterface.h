// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "KerraInteractInterface.generated.h"


UINTERFACE(MinimalAPI)
class UKerraInteractInterface : public UInterface
{
	GENERATED_BODY()
};


class KERRA_API IKerraInteractInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DoInteraction(AActor* TargetActor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FGameplayTag GetInteractionTargetTag();
};
