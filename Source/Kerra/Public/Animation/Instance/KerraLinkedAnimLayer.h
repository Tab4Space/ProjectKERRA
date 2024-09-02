// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/Instance/KerraAnimInstanceBase.h"
#include "KerraLinkedAnimLayer.generated.h"


class UKerraHeroAnimInstance;

UCLASS()
class KERRA_API UKerraLinkedAnimLayer : public UKerraAnimInstanceBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, meta=(BlueprintThreadSafe))
	UKerraHeroAnimInstance* GetKerraPlayerAnimInstance() const;
};
