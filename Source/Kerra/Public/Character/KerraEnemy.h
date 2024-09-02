// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/KerraCharacterBase.h"
#include "KerraEnemy.generated.h"


class UWidgetComponent;
class UEnemyUIComponent;
class UEnemyCombatComponent;

UCLASS()
class KERRA_API AKerraEnemy : public AKerraCharacterBase
{
	GENERATED_BODY()

public:
	AKerraEnemy();

	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }

	/* Combat Interface */
	virtual UKerraCombatComponent* GetKerraCombatComponent() const override;

	/* UI Interface */
	virtual UKerraUIComponent* GetPawnUIComponent() const override;
	virtual UEnemyUIComponent* GetEnemyUIComponent() const override;

	
protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	

private:
	virtual void InitAbilityActorInfo() override;
	void InitStartupData();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat")
	TObjectPtr<UEnemyCombatComponent> EnemyCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UI")
	TObjectPtr<UEnemyUIComponent> UIComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UI")
	TObjectPtr<UWidgetComponent> EnemyHealthWidgetComponent; 
	
};
