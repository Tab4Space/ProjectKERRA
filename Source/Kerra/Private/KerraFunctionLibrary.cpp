// Fill out your copyright notice in the Description page of Project Settings.


#include "KerraFunctionLibrary.h"
#include "AbilitySystem/KerraAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Interface/KerraCombatInterface.h"
#include "GenericTeamAgentInterface.h"
#include "KerraGameplayTags.h"
#include "Game/KerraGameInstance.h"
#include "Interface/KerraInventoryInterface.h"
#include "Interface/KerraQuestInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "Struct/KerraCountDownAction.h"
#include "UI/HUD/KerraHUD.h"
#include "Kismet/GameplayStatics.h"



UKerraAbilitySystemComponent* UKerraFunctionLibrary::NativeGetKerraASCFromActor(AActor* InActor)
{
	check(InActor);
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor);
	if(ASC)
	{
		return CastChecked<UKerraAbilitySystemComponent>(ASC);	
	}
	return nullptr;
}

void UKerraFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	// Add tag to player character
	UKerraAbilitySystemComponent* ASC = NativeGetKerraASCFromActor(InActor);
	if(!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		// 이 함수를 사용하면 같은 Tag를 여러 번 추가할 수 없다
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

void UKerraFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	// Remove tag to player character
	UKerraAbilitySystemComponent* ASC = NativeGetKerraASCFromActor(InActor);
	if(ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}

bool UKerraFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	UKerraAbilitySystemComponent* ASC = NativeGetKerraASCFromActor(InActor);
	if(ASC)
	{
		return ASC->HasMatchingGameplayTag(TagToCheck);	
	}
	return false;
}

void UKerraFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EKerraConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck) ? EKerraConfirmType::Yes : EKerraConfirmType::No; 
}

UKerraCombatComponent* UKerraFunctionLibrary::NativeGetKerraCombatComponentFromActor(AActor* InActor)
{
	check(InActor)

	if(IKerraCombatInterface* CombatInterface = Cast<IKerraCombatInterface>(InActor))
	{
		return CombatInterface->GetKerraCombatComponent();
	}
	return nullptr;
}

UKerraCombatComponent* UKerraFunctionLibrary::BP_GetKerraCombatComponentFromActor(AActor* InActor, EKerraValidType& OutValidType)
{
	UKerraCombatComponent* CombatComponent = NativeGetKerraCombatComponentFromActor(InActor);
	OutValidType = CombatComponent ? EKerraValidType::Valid : EKerraValidType::Invalid;
	return CombatComponent;
}

UKerraQuestComponent* UKerraFunctionLibrary::NativeGetKerraQuestComponentFromActor(AActor* InActor)
{
	check(InActor);

	if(IKerraQuestInterface* QuestInterface = Cast<IKerraQuestInterface>(InActor))
	{
		return QuestInterface->GetKerraQuestComponent();
	}
	return nullptr;
}

UKerraInventoryComponent* UKerraFunctionLibrary::NativeGetKerraInventoryComponentFromActor(AActor* InActor)
{
	check(InActor);

	if(IKerraInventoryInterface* InventoryInterface = Cast<IKerraInventoryInterface>(InActor))
	{
		return InventoryInterface->GetKerraInventoryComponent();
	}
	return nullptr;
}

bool UKerraFunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
	check(QueryPawn && TargetPawn);
	
	IGenericTeamAgentInterface* QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

	if(QueryTeamAgent && TargetTeamAgent)
	{
		return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
	}
	return false;
}

float UKerraFunctionLibrary::GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel)
{
	return InScalableFloat.GetValueAtLevel(InLevel);
}

FGameplayTag UKerraFunctionLibrary::ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDiffernce)
{
	check(InAttacker && InVictim);

	const FVector VictimForward = InVictim->GetActorForwardVector();
	const FVector VictimToAttackerNorm = (InAttacker->GetActorLocation() - InVictim->GetActorLocation()).GetSafeNormal();

	const float DotResult = FVector::DotProduct(VictimForward, VictimToAttackerNorm);
	OutAngleDiffernce = UKismetMathLibrary::DegAcos(DotResult);

	const FVector CrossResult = FVector::CrossProduct(VictimForward, VictimToAttackerNorm);
	if(CrossResult.Z < 0.f)
	{
		OutAngleDiffernce *= -1.f;
	}

	if(OutAngleDiffernce >= -45.f && OutAngleDiffernce <= 45.f)
	{
		return KerraGameplayTags::Shared_Status_HitReact_Front;
	}
	else if(OutAngleDiffernce < -45.f && OutAngleDiffernce > -135.f)
	{
		return KerraGameplayTags::Shared_Status_HitReact_Left;
	}
	else if (OutAngleDiffernce < -135.f || OutAngleDiffernce >135.f)
	{
		return KerraGameplayTags::Shared_Status_HitReact_Back;
	}
	else if (OutAngleDiffernce > 45.f && OutAngleDiffernce <= 135.f)
	{
		return KerraGameplayTags::Shared_Status_HitReact_Right;
	}

	return KerraGameplayTags::Shared_Status_HitReact_Front;
}

bool UKerraFunctionLibrary::IsValidBlock(AActor* InAttacker, AActor* InDefender)
{
	// check valid block direction
	check(InAttacker && InDefender);

	const float DotResult = FVector::DotProduct(InAttacker->GetActorForwardVector(), InDefender->GetActorForwardVector());
	return DotResult < -0.1f;
}

bool UKerraFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(AActor* Instigator, AActor* TargetActor, FGameplayEffectSpecHandle& InSpecHandle)
{
	UKerraAbilitySystemComponent* SourceASC = NativeGetKerraASCFromActor(Instigator);
	UKerraAbilitySystemComponent* TargetASC = NativeGetKerraASCFromActor(TargetActor);

	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = SourceASC->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data, TargetASC);
	return ActiveGameplayEffectHandle.WasSuccessfullyApplied();
}

void UKerraFunctionLibrary::CountDown(const UObject* WorldContextObject, float TotalTime, float UpdateInterval, float& OutRemainingTime, EKerraCountDownActionInput CountDownInput, UPARAM(DisplayName="Output")EKerraCountDownOutput& CountDownOutput, FLatentActionInfo LatentInfo)
{
	UWorld* World = nullptr;
	if(GEngine)
	{
		World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	}

	if(!World)
	{
		return;
	}

	FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
	FKerraCountDownAction* FoundAction = LatentActionManager.FindExistingAction<FKerraCountDownAction>(LatentInfo.CallbackTarget, LatentInfo.UUID);

	if(CountDownInput == EKerraCountDownActionInput::Start)
	{
		// new operator is managed from memory. So don't care about memory leak.
		if(!FoundAction)
		{
			LatentActionManager.AddNewAction(
				LatentInfo.CallbackTarget,
				LatentInfo.UUID,
				new FKerraCountDownAction(TotalTime, UpdateInterval, OutRemainingTime, CountDownOutput, LatentInfo)
			);
		}
	}

	if(CountDownInput == EKerraCountDownActionInput::Cancel)
	{
		if(FoundAction)
		{
			FoundAction->CancelAction();
		}
	}
}

AKerraHUD* UKerraFunctionLibrary::NativeGetKerraHUD(APlayerController* PC)
{
	return Cast<AKerraHUD>(PC->GetHUD());
}

AKerraHUD* UKerraFunctionLibrary::BP_GetKerraHUD(APlayerController* PC)
{
	return NativeGetKerraHUD(PC);
}

FKerraQuestData UKerraFunctionLibrary::GetQuestDataByTagFromKerraGI(FGameplayTag InQuestTag, AActor* ObjectActor)
{
	UKerraGameInstance* KerraGI = Cast<UKerraGameInstance>(UGameplayStatics::GetGameInstance(ObjectActor));
	checkf(KerraGI, TEXT("Not valid Kerra Game Instance"));
	
	UDataTable* QuestDT = KerraGI->GetQuestDataTable();
	checkf(QuestDT, TEXT("Check Quset Data Table in BP_KerraGI"));

	if(FKerraQuestData* FoundQuestInfo = QuestDT->FindRow<FKerraQuestData>(InQuestTag.GetTagName(), ""))
	{
		return *FoundQuestInfo;
	}
	return FKerraQuestData();
}

FKerraItemData UKerraFunctionLibrary::GetItemDataByTagFromKerraGI(FGameplayTag InItemTag, AActor* ObjectActor)
{
	UKerraGameInstance* KerraGI = Cast<UKerraGameInstance>(UGameplayStatics::GetGameInstance(ObjectActor));
	checkf(KerraGI, TEXT("Not valid Kerra Game Instance"));
	
	UDataTable* ItemDT = KerraGI->GetItemDataTable();
	checkf(ItemDT, TEXT("Check Quset Data Table in BP_KerraGI"));

	if(FKerraItemData* FoundItemInfo = ItemDT->FindRow<FKerraItemData>(InItemTag.GetTagName(), ""))
	{
		return *FoundItemInfo;
	}
	return FKerraItemData();
}

FKerraSkillData UKerraFunctionLibrary::GetSkillDataByTagFromKerraGI(FGameplayTag InSkillTag, AActor* ObjectActor)
{
	UKerraGameInstance* KerraGI = Cast<UKerraGameInstance>(UGameplayStatics::GetGameInstance(ObjectActor));
	checkf(KerraGI, TEXT("Not valid Kerra Game Instance"));

	UDataTable* SkillDT = KerraGI->GetSkillDataTable();
	checkf(SkillDT, TEXT("Check Skill Data Table in BP_KerraGI"));

	if(FKerraSkillData* FoundSkillInfo = SkillDT->FindRow<FKerraSkillData>(InSkillTag.GetTagName(), ""))
	{
		return *FoundSkillInfo;
	}
	
	return FKerraSkillData();
}




