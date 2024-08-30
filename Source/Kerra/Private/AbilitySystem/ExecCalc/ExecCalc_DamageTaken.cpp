// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ExecCalc/ExecCalc_DamageTaken.h"
#include "KerraGameplayTags.h"
#include "AbilitySystem/KerraAttributeSet.h"

struct FKerraDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken);

	FKerraDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UKerraAttributeSet, AttackPower, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UKerraAttributeSet, DefensePower, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UKerraAttributeSet, DamageTaken, Target, false);
	}
};

static const FKerraDamageCapture GetKerraDamageCapture()
{
	static FKerraDamageCapture KerraDamageCapture;
	return KerraDamageCapture;
}

UExecCalc_DamageTaken::UExecCalc_DamageTaken()
{
	// Need constructor for attribute capture

	/* Slow method */
	/*FProperty* AttackPwoerProperty = FindFieldChecked<FProperty>(UKerraAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UKerraAttributeSet, AttackPower));

	// true: GE가 끝난 직후에 캡처
	// false: GE가 적용될 때 캡처 > 버프/디버프 같은게 없을 때
	FGameplayEffectAttributeCaptureDefinition AttackPowerCaptureDefinition(AttackPwoerProperty, EGameplayEffectAttributeCaptureSource::Source, false);
	RelevantAttributesToCapture.Add(AttackPowerCaptureDefinition);*/

	/* Fast method */
	RelevantAttributesToCapture.Add(GetKerraDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetKerraDamageCapture().DefensePowerDef);
	RelevantAttributesToCapture.Add(GetKerraDamageCapture().DamageTakenDef);
}

void UExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	// 이 함수에서 최종 damage를 계산하기 위한 모든 관련 값ㅇ르 얻을 수 있다
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	/*
	// Use these functions when get data from Gameplay Effect Spec
	EffectSpec.GetContext().GetSourceObject();
	EffectSpec.GetContext().GetAbility();
	EffectSpec.GetContext().GetInstigator();
	EffectSpec.GetContext().GetEffectCauser();
	*/
	
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttackPower = 0.f;
	UE_LOG(LogTemp, Warning, TEXT("%f"), SourceAttackPower);
	// 이 함수를 거치면서 SourceAttack 변수에 Attribute Set에 있는 캡처된 AttackPower 값이 들어간다 
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetKerraDamageCapture().AttackPowerDef, EvaluateParameters, SourceAttackPower);

	float BaseDamage = 0.f;
	int32 UsedLightAttackComboCount = 0;
	int32 UsedHeavyAttackComboCount = 0;
	for(const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if(TagMagnitude.Key.MatchesTagExact(KerraGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
			UE_LOG(LogTemp, Warning, TEXT("%f"), BaseDamage);
		}
		if(TagMagnitude.Key.MatchesTagExact(KerraGameplayTags::Player_SetByCaller_AttackType_Light))
		{
			UsedLightAttackComboCount = TagMagnitude.Value;
			UE_LOG(LogTemp, Warning, TEXT("%d"), UsedLightAttackComboCount);
		}
		if(TagMagnitude.Key.MatchesTagExact(KerraGameplayTags::Player_SetByCaller_AttackType_Heavy))
		{
			UsedHeavyAttackComboCount = TagMagnitude.Value;
			UE_LOG(LogTemp, Warning, TEXT("%d"), UsedHeavyAttackComboCount);
			
		}
	}
	
	float TargetDefensePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetKerraDamageCapture().DefensePowerDef, EvaluateParameters, TargetDefensePower);
	UE_LOG(LogTemp, Warning, TEXT("%f"), TargetDefensePower);
	
	if(UsedLightAttackComboCount != 0)
	{
		const float DamageIncreasePercentLight = (UsedLightAttackComboCount - 1) * 0.05f + 1.f;
		BaseDamage *= DamageIncreasePercentLight;
		UE_LOG(LogTemp, Warning, TEXT("%f"), BaseDamage);
	}

	if(UsedHeavyAttackComboCount != 0)
	{
		const float DamageIncreasePercentHeavy = UsedHeavyAttackComboCount * 0.15f + 1.f;
		BaseDamage *= DamageIncreasePercentHeavy;
		UE_LOG(LogTemp, Warning, TEXT("%f"), BaseDamage);
	}

	// If it is not suitable game, change this equation
	const float FinalDamage = BaseDamage * SourceAttackPower / TargetDefensePower;
	UE_LOG(LogTemp, Warning, TEXT("%f"), FinalDamage);
	if(FinalDamage > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetKerraDamageCapture().DamageTakenProperty, EGameplayModOp::Override, FinalDamage));
	}
}
