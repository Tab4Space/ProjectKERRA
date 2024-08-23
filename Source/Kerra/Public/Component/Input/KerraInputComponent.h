// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAsset/KerraInputConfig.h"
#include "KerraInputComponent.generated.h"


UCLASS()
class KERRA_API UKerraInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserObject, typename CallbackFunc>
	void BindNativeInputAction(const UKerraInputConfig* InInputConfig,const FGameplayTag& InInputTag,ETriggerEvent TriggerEvent,UserObject* ContextObject,CallbackFunc Func);
};

template <class UserObject, typename CallbackFunc>
inline void UKerraInputComponent::BindNativeInputAction(const UKerraInputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func)
{
	checkf(InInputConfig, TEXT("Input config data asset is null, can not bind"));

	if(UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundAction, TriggerEvent, ContextObject, Func);
	}
	
}
