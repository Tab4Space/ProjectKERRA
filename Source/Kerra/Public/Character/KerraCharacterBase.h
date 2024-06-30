// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KerraCharacterBase.generated.h"

UCLASS()
class KERRA_API AKerraCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AKerraCharacterBase();

protected:
	virtual void BeginPlay() override;


};
