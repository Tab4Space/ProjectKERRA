// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/KerraInputConfig.h"

UInputAction* UKerraInputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
	for(const FKerraInputActionConfig& InputActionConfig : NativeInputActions)
	{
		if(InputActionConfig.InputTag == InInputTag && InputActionConfig.InputAction)
		{
			return InputActionConfig.InputAction;
		}
	}
	return nullptr;
}
