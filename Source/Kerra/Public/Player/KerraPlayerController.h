// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "KerraPlayerController.generated.h"


class UInputMappingContext;


UCLASS()
class KERRA_API AKerraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AKerraPlayerController();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> KerraContext;
	
};
