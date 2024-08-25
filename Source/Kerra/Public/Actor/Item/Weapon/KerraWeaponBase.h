// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KerraWeaponBase.generated.h"


class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class KERRA_API AKerraWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:
	AKerraWeaponBase();

	FORCEINLINE UBoxComponent* GetWeaponCollisionBox() const { return WeaponCollisionBox; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon")
	TObjectPtr<UStaticMeshComponent> WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon")
	TObjectPtr<UBoxComponent> WeaponCollisionBox;
};
