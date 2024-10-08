// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/Combat/KerraCombatComponent.h"
#include "EnemyCombatComponent.generated.h"


UCLASS()
class KERRA_API UEnemyCombatComponent : public UKerraCombatComponent
{
	GENERATED_BODY()

public:
	virtual void OnHitTargetActor(AActor* HitActor) override;

protected:
	virtual void ToggleHandCollisionBox(bool bShouldEnable, EToggleDamageType ToggleDamageType) override;
};
