// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "GenericTeamAgentInterface.h"
#include "KerraPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnToggoleQuestWidgetSignature);

class UInputMappingContext;
class UInputAction;
class UKerraInputDataAsset;
class UKerraAbilitySystemComponent;

UCLASS()
class KERRA_API AKerraPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	AKerraPlayerController();

	/* Interface */
	virtual FGenericTeamId GetGenericTeamId() const override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void Move(const FInputActionValue& InputActionValue);
	void LookAt(const FInputActionValue& InputActionValue);

	void Input_SwitchTargetTriggered(const FInputActionValue& InputActionValue);
	void Input_SwitchTargetCompleted(const FInputActionValue& InputActionValue);

	void Input_PickUpStarted(const FInputActionValue& InputActionValue);

	void Input_Quest(const FInputActionValue& InputActionValue);
	void Input_Inventory(const FInputActionValue& InputActionValue);

	void AbilityInputPressed(FGameplayTag InInputTag);
	void AbilityInputReleased(FGameplayTag InInputTag);

	UKerraAbilitySystemComponent* GetASC();	

public:
	UPROPERTY(BlueprintAssignable)
	FOnToggoleQuestWidgetSignature OnToggleQuestWidget; 

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="CharacterData", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UKerraInputDataAsset> InputConfigDataAsset;

	TObjectPtr<UKerraAbilitySystemComponent> KerraAbilitySystemComponent;

	FGenericTeamId HeroTeamID;

	UPROPERTY()
	FVector2D SwitchDirection = FVector2D::ZeroVector;
	
};
