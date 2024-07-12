// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "KerraPlayerController.generated.h"


struct FInputActionValue;
class UInputMappingContext;
class UInputAction;


UCLASS()
class KERRA_API AKerraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AKerraPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> KerraContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& InputActionValue);
	
};
