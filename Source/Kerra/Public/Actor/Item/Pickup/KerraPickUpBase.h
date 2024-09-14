// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KerraPickUpBase.generated.h"


class USphereComponent;

UCLASS()
class KERRA_API AKerraPickUpBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AKerraPickUpBase();

protected:
	UFUNCTION()
	virtual void OnPickUpCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Pick Up Interaction")
	TObjectPtr<USphereComponent> PickUpCollsion;
	

};
