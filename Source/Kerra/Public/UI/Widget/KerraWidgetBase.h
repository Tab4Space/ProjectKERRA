// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KerraWidgetBase.generated.h"

class AKerraHUD;
class UEnemyUIComponent;
class UHeroUIComponent;
class UKerraQuestComponent;
class UKerraInventoryComponent;


UCLASS()
class KERRA_API UKerraWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void InitEnemyCreatedWidget(AActor* OwningEnemyActor);

	/* Widget Utility*/
	virtual void ToggleShowingWindow();

	/* Getter */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	AKerraHUD* GetKerraHUD();

protected:
	// 위젯이 생성된 후 한 번만 호출되는 함수
	virtual void NativeOnInitialized() override;

	// Get player's ui component
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="OnOwningPlayerUIComponentInitialized"))
	void BP_OnOwningPlayerUIComponentInitialized(UHeroUIComponent* OwningPlayerUIComponent);

	// Get enemy's ui component's
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="OnOwningEnemyUIComponentInitialized"))
	void BP_OnOwningEnemyUIComponentInitialized(UEnemyUIComponent* OwningEnemyUIComponent);

	// Get player's quest component
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="OnOwningQuestComponentInitialized"))
	void BP_OnOwningPlayerQuestComponentIntialized(UKerraQuestComponent* OwningPlayerQuestComponent);

	// Get player's inventory component
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="OnOwningInventoryComponentInitialized"))
	void BP_OnOwningInventoryComponentInitialized(UKerraInventoryComponent* OwningKerraInventoryComponent);

	UFUNCTION(BlueprintCallable)
	void SetUIMode(bool IsShowing);
	
};
