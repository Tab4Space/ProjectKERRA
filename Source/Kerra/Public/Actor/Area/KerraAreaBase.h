// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KerraAreaBase.generated.h"

class UBoxComponent;
UCLASS()
class KERRA_API AKerraAreaBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AKerraAreaBase();

protected:
	UFUNCTION()
	virtual void OnBoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Area")
	TObjectPtr<UBoxComponent> AreaCollision;


};
