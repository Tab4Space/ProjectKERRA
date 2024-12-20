// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "KerraInventoryInterface.generated.h"

class UKerraInventoryComponent;

UINTERFACE(MinimalAPI)
class UKerraInventoryInterface : public UInterface
{
	GENERATED_BODY()
};


class KERRA_API IKerraInventoryInterface
{
	GENERATED_BODY()

public:
	virtual UKerraInventoryComponent* GetKerraInventoryComponent() const = 0;
};
