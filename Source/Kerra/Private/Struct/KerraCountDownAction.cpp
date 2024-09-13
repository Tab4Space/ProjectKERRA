// Fill out your copyright notice in the Description page of Project Settings.


#include "Struct/KerraCountDownAction.h"

void FKerraCountDownAction::CancelAction()
{
	bNeedCancel = true;
}

void FKerraCountDownAction::UpdateOperation(FLatentResponse& Response)
{
	// if canceled
	if(bNeedCancel)
	{
		CountDownOutput = EKerraCountDownOutput::Cancel;
		Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
		return;
	}

	// if finish count down normally
	if(ElapsedTimeSinceStart >= TotalCountDownTime)
	{
		CountDownOutput = EKerraCountDownOutput::Completed;
		Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
		return;
	}

	// less elapsed interval than update interval
	if(ElapsedInterval < UpdateInterval)
	{
		// same tick's DeltaTime
		ElapsedInterval += Response.ElapsedTime();
	}
	else
	{
		ElapsedTimeSinceStart += UpdateInterval > 0.f ? UpdateInterval : Response.ElapsedTime();
		OutRemainingTime = TotalCountDownTime - ElapsedTimeSinceStart;
		CountDownOutput = EKerraCountDownOutput::Updated;

		// Finish count down task
		Response.TriggerLink(ExecutionFunction, OutputLink, CallbackTarget);
		ElapsedInterval = 0.f;
	}
	
}
