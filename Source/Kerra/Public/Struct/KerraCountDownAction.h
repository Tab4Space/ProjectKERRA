// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KerraEnumTypes.h"

class FKerraCountDownAction : public FPendingLatentAction
{
public:
	FKerraCountDownAction(float InTotalCountDownTime, float InUpdateInterval, float& InOutRemainingTime, EKerraCountDownOutput& InCountDownOutput, const FLatentActionInfo& LatentInfo)
	: bNeedCancel(false), TotalCountDownTime(InTotalCountDownTime), UpdateInterval(InUpdateInterval), OutRemainingTime(InOutRemainingTime), CountDownOutput(InCountDownOutput),
	ExecutionFunction(LatentInfo.ExecutionFunction), OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget), ElapsedInterval(0.f), ElapsedTimeSinceStart(0.f)
	{
	}

	void CancelAction();

	// This function execute every tick.
	virtual void UpdateOperation(FLatentResponse& Response) override;

private:
	bool bNeedCancel;
	float TotalCountDownTime;
	float UpdateInterval;
	float& OutRemainingTime;
	EKerraCountDownOutput& CountDownOutput;
	FName ExecutionFunction;
	int32 OutputLink;
	FWeakObjectPtr CallbackTarget;
	float ElapsedInterval;
	float ElapsedTimeSinceStart;
};
