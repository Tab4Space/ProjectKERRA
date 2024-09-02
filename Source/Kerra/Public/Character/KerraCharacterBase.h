// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interface/KerraCombatInterface.h"
#include "Interface/KerraWidgetInterface.h"
#include "KerraCharacterBase.generated.h"


class UKerraStartUpDataAssetBase;
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class KERRA_API AKerraCharacterBase : public ACharacter, public IAbilitySystemInterface, public IKerraCombatInterface, public IKerraWidgetInterface
{
	GENERATED_BODY()

public:
	AKerraCharacterBase();

	/* Ability System */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	/* Combat Interface */
	virtual UKerraCombatComponent* GetKerraCombatComponent() const override;

	/* UI Interface */
	virtual UKerraUIComponent* GetPawnUIComponent() const override;

protected:
	virtual void InitAbilityActorInfo();
	virtual void BeginPlay() override;
	

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem")
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="CharacterData")
	TSoftObjectPtr<UKerraStartUpDataAssetBase> CharacterStartupData;

};
