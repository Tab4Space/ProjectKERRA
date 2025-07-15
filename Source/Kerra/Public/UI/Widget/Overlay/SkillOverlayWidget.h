// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/Overlay/KerraOverlayWidget.h"
#include "SkillOverlayWidget.generated.h"

/**
 * 
 */
UCLASS()
class KERRA_API USkillOverlayWidget : public UKerraOverlayWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void InitSkillOverlay(UKerraOverlayWidget* InParentWidget);

	virtual void BindEvents() override;

	UFUNCTION(BlueprintNativeEvent)
	void OnChangeSkillPoints(int32 InPoints);
	virtual void OnChangeSkillPoints_Implementation(int32 InPoints);

protected:
	virtual void NativeOnInitialized() override;
};
