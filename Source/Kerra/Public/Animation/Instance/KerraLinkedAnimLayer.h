// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/Instance/KerraBaseAnimInstance.h"
#include "KerraLinkedAnimLayer.generated.h"


class UKerraPlayerAnimInstance;

UCLASS()
class KERRA_API UKerraLinkedAnimLayer : public UKerraBaseAnimInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, meta=(BlueprintThreadSafe))
	UKerraPlayerAnimInstance* GetKerraPlayerAnimInstance() const;
};
