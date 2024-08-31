// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/KerraAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "KerraFunctionLibrary.h"
#include "KerraGameplayTags.h"

UKerraAttributeSet::UKerraAttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitCurrentRage(1.f);
	InitMaxRage(1.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);
}

void UKerraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	// GE를 갖고 Attribute의 값을 변경하고 싶을 때 사용하는 함수
	if(Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		// GE를 사용해 CurrentHealth를 수정
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);
	}

	if(Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		const float NewCurrentRage = FMath::Clamp(GetCurrentRage(), 0.f, GetMaxRage());
		SetCurrentRage(NewCurrentRage);
	}

	if(Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetCurrentHealth();
		const float Damage = GetDamageTaken();

		const float NewCurrentHealth = FMath::Clamp(OldHealth-Damage, 0.f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);
		
		// TODO: Notify the UI
		
		if (NewCurrentHealth == 0.f)
		{
			UKerraFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), KerraGameplayTags::Shared_Status_Dead);
		}
	}
	
}
