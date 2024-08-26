// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "KerraPlayerController.generated.h"


class UInputMappingContext;
class UInputAction;
class UKerraInputConfig;
class UKerraAbilitySystemComponent;


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
	/*
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> LookAction;
	*/
	

	void Move(const FInputActionValue& InputActionValue);
	void LookAt(const FInputActionValue& InputActionValue);

	void AbilityInputPressed(FGameplayTag InInputTag);
	void AbilityInputReleased(FGameplayTag InInputTag);

	UKerraAbilitySystemComponent* GetASC();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="CharacterData", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UKerraInputConfig> InputConfigDataAsset;

	TObjectPtr<UKerraAbilitySystemComponent> KerraAbilitySystemComponent;
	
};
