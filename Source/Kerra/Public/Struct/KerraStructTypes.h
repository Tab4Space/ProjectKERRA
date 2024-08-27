// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KerraStructTypes.generated.h" 

class UKerraLinkedAnimLayer;

USTRUCT(BlueprintType)
struct FKerraPlayerWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UKerraLinkedAnimLayer> WeaponAnimLayerToLink;
	
};