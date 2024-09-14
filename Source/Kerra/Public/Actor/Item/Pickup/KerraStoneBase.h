// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Item/Pickup/KerraPickUpBase.h"
#include "KerraStoneBase.generated.h"


class UGameplayEffect;
class UKerraAbilitySystemComponent;

UCLASS()
class KERRA_API AKerraStoneBase : public AKerraPickUpBase
{
	GENERATED_BODY()

public:
	void Consume(UKerraAbilitySystemComponent* InASC, int32 ApplyLevel);

protected:
	virtual void OnPickUpCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="On Stone Consume"))
	void BP_OnStoneConsumed();

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> StoneGameplayEffectClass;
	
};
