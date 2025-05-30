#pragma once

#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "KerraSkillData.generated.h"

class UKerraGameplayAbility;

UENUM(BlueprintType, Blueprintable)
enum class ESkillActType : uint8
{
	PassiveSkill,
	ActiveSkill
};

UENUM(BlueprintType, Blueprintable)
enum class ESkillCategory : uint8
{
	AttackSkill,
	DefenseSkill,
	SurviveSkill
};

USTRUCT(BlueprintType)
struct FKerraSkillData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FKerraSkillData();

	// skill unique tag
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Categories="Player.Ability.Skill"))
	FGameplayTag SkillTag;		

	// skill unique number
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AbilityID;			

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SkillName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SkillDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UKerraGameplayAbility> SkillClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTexture2D> SkillIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Categories="Player.Ability.Skill"))
	FGameplayTagContainer RequiredSkills;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESkillActType SkillActType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESkillCategory SkillCategory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 InitLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RequiredPoints;
	
	bool IsValid() const { return SkillTag.IsValid(); }

	bool operator==(const FKerraSkillData& Other) const
	{
		if(SkillTag != Other.SkillTag)
		{
			return false;
		}
		return true;
	}
};
