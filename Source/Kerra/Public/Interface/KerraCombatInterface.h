// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "KerraCombatInterface.generated.h"

class UKerraCombatComponent;

UINTERFACE(MinimalAPI)
class UKerraCombatInterface : public UInterface
{
	GENERATED_BODY()
};


class KERRA_API IKerraCombatInterface
{
	GENERATED_BODY()

public:
	virtual UKerraCombatComponent* GetKerraCombatComponent() const = 0;
};
