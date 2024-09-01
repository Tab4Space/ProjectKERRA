// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/KerraAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "KerraFunctionLibrary.h"
#include "KerraGameplayTags.h"
#include "Interface/KerraUIInterface.h"
#include "Component/UI/PawnUIComponent.h"
#include "Component/UI/KerraPlayerUIComponent.h"

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
	if(!CachedUIInterface.IsValid())
	{
		CachedUIInterface = TWeakInterfacePtr<IKerraUIInterface>(Data.Target.GetAvatarActor());
		// CachedUIInterface = Cast<IKerraUIInterface>(Data.Target.GetAvatarActor());
	}
	checkf(CachedUIInterface.IsValid(), TEXT("%s is not implement ui interface"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());

	UPawnUIComponent* UIComponent = CachedUIInterface->GetPawnUIComponent();
	checkf(UIComponent, TEXT("%s no UI Component"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel())
	
	// GE를 갖고 Attribute의 값을 변경하고 싶을 때 사용하는 함수
	if(Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		// GE를 사용해 CurrentHealth를 수정
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);
		UIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
	}

	if(Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		const float NewCurrentRage = FMath::Clamp(GetCurrentRage(), 0.f, GetMaxRage());
		SetCurrentRage(NewCurrentRage);

		if(UKerraPlayerUIComponent* PlayerUIComponent = CachedUIInterface->GetPlayerUIComponent())
		{
			PlayerUIComponent->OnCurrentRageChanged.Broadcast(GetCurrentRage() / GetMaxRage());
		}
	}

	if(Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetCurrentHealth();
		const float Damage = GetDamageTaken();

		const float NewCurrentHealth = FMath::Clamp(OldHealth-Damage, 0.f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);
		UIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());

		if (GetCurrentHealth() == 0.f)
		{
			UKerraFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), KerraGameplayTags::Shared_Status_Dead);
		}
	}
	
}
