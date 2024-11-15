// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Area/KerraAreaBase.h"
#include "Struct/KerraQuestInfo.h"
#include "DestLocationBase.generated.h"


UCLASS()
class KERRA_API ADestLocationBase : public AKerraAreaBase
{
	GENERATED_BODY()

protected:
	virtual void OnBoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Area")
	EQuestArea AreaName;
};
