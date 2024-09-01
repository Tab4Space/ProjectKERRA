// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "KerraUIInterface.generated.h"


class UKerraEnemyUIComponent;
class UKerraPlayerUIComponent;
class UPawnUIComponent;

UINTERFACE(MinimalAPI)
class UKerraUIInterface : public UInterface
{
	GENERATED_BODY()
};


class KERRA_API IKerraUIInterface
{
	GENERATED_BODY()

public:
	virtual UPawnUIComponent* GetPawnUIComponent() const = 0;
	virtual UKerraPlayerUIComponent* GetPlayerUIComponent() const;
	virtual UKerraEnemyUIComponent* GetEnemyUIComponent() const;
};
