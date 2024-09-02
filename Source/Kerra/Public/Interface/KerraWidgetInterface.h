// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "KerraWidgetInterface.generated.h"


class UKerraUIComponent;
class UHeroUIComponent;
class UEnemyUIComponent;

UINTERFACE(MinimalAPI)
class UKerraWidgetInterface : public UInterface
{
	GENERATED_BODY()
};


class KERRA_API IKerraWidgetInterface
{
	GENERATED_BODY()

public:
	virtual UKerraUIComponent* GetPawnUIComponent() const = 0;
	virtual UHeroUIComponent* GetPlayerUIComponent() const;
	virtual UEnemyUIComponent* GetEnemyUIComponent() const;
};
