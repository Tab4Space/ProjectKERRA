// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/KerraCharacterBase.h"
#include "KerraEnemy.generated.h"


class UKerraEnemyCombatComponent;

UCLASS()
class KERRA_API AKerraEnemy : public AKerraCharacterBase
{
	GENERATED_BODY()

public:
	AKerraEnemy();

	virtual void BeginPlay() override;

	FORCEINLINE UKerraEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }

protected:
	virtual void PossessedBy(AController* NewController) override;

private:
	virtual void InitAbilityActorInfo() override;
	void InitStartupData();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat")
	TObjectPtr<UKerraEnemyCombatComponent> EnemyCombatComponent;

	
};
