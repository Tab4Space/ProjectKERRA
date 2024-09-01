// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/KerraCharacterBase.h"
#include "KerraEnemy.generated.h"


class UWidgetComponent;
class UKerraEnemyUIComponent;
class UKerraEnemyCombatComponent;

UCLASS()
class KERRA_API AKerraEnemy : public AKerraCharacterBase
{
	GENERATED_BODY()

public:
	AKerraEnemy();

	FORCEINLINE UKerraEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }

	/* Combat Interface */
	virtual UKerraCombatComponent* GetKerraCombatComponent() const override;

	/* UI Interface */
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	virtual UKerraEnemyUIComponent* GetEnemyUIComponent() const override;

	
protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	

private:
	virtual void InitAbilityActorInfo() override;
	void InitStartupData();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat")
	TObjectPtr<UKerraEnemyCombatComponent> EnemyCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UI")
	TObjectPtr<UKerraEnemyUIComponent> UIComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UI")
	TObjectPtr<UWidgetComponent> EnemyHealthWidgetComponent; 
	
};
