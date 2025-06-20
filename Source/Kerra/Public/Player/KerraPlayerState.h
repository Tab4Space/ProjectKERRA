// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "KerraPlayerState.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerStateChanged, int32, InValue);

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class KERRA_API AKerraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AKerraPlayerState();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return KerraAS; }

	void AddSkillPoints(int32 InSkillPoints);

	/* Getter */
	FORCEINLINE int32 GetSkillPoints() const { return SkillPoints; }

	/* Setter */
	void SetSkillPoints(int32 InSkillPoints);
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> KerraASC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem")
	TObjectPtr<UAttributeSet> KerraAS;

public:
	UPROPERTY(BlueprintAssignable)
	FOnPlayerStateChanged OnSkillPointsChanged;

private:
	UPROPERTY(VisibleAnywhere)
	int32 SkillPoints = 0;
	
};
