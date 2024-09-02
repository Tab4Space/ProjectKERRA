// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "KerraAIController.generated.h"


class UAIPerceptionComponent;
class UAISenseConfig_Sight;

UCLASS()
class KERRA_API AKerraAIController : public AAIController 
{
	GENERATED_BODY()

public:
	AKerraAIController(const FObjectInitializer& ObjectInitializer);

	/* Interface */
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAIPerceptionComponent> EnemyPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAISenseConfig_Sight> AISenseConfig_Sight;

private:
	/* On/Off detour avoidance */
	UPROPERTY(EditDefaultsOnly, Category="DetourCrowdAvoidanceConfig", meta=(AllowPrivateAccess="true"))
	bool bEnableDetourCrowdAvoidance = true;

	/* Set detour avoidance quality*/
	UPROPERTY(EditDefaultsOnly, Category="DetourCrowdAvoidanceConfig", meta=(AllowPrivateAccess="true", EditCondition="bEnableDetourCrowdAvoidance", UIMin="1", UIMax="4"))
	int32 DetourCrowdAvoidanceQuality = 4;

	/* */
	UPROPERTY(EditDefaultsOnly, Category="DetourCrowdAvoidanceConfig", meta=(AllowPrivateAccess="true", EditCondition="bEnableDetourCrowdAvoidance"))
	float CollisionQueryRange = 600.f;
};
