// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KerraWidgetBase.generated.h"


class UEnemyUIComponent;
class UHeroUIComponent;
class UKerraQuestComponent;

UCLASS()
class KERRA_API UKerraWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void InitEnemyCreatedWidget(AActor* OwningEnemyActor);
	

protected:
	// 위젯이 생성된 후 한 번만 호출되는 함수
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="OnOwningPlayerUIComponentInitialized"))
	void BP_OnOwningPlayerUIComponentInitialized(UHeroUIComponent* OwningPlayerUIComponent);

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="OnOwningEnemyUIComponentInitialized"))
	void BP_OnOwningEnemyUIComponentInitialized(UEnemyUIComponent* OwningEnemyUIComponent);

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="OnOwningQuestComponentInitialized"))
	void BP_OnOwningPlayerQuestComponentIntialized(UKerraQuestComponent* OwningPlayerQuestComponent);
};
