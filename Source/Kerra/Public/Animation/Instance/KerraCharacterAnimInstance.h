// Anim Instance for player and enemy
// Shared by player and enemy

#pragma once

#include "CoreMinimal.h"
#include "Animation/Instance/KerraAnimInstanceBase.h"
#include "Struct/KerraEnumTypes.h"
#include "KerraCharacterAnimInstance.generated.h"


class AKerraCharacterBase;
class UCharacterMovementComponent;

UCLASS()
class KERRA_API UKerraCharacterAnimInstance : public UKerraAnimInstanceBase
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativePostEvaluateAnimation() override;

protected:
	UFUNCTION(BlueprintCallable, Category="KerraLocomotion|Advanced")
	void FindLocomotionState();

	UFUNCTION(BlueprintCallable, Category="KerraLocomotion|Advanced")
	void FindLocomotionStartDirection(const float StartAngle);

	UFUNCTION(BlueprintCallable, Category="KerraLocomotion|Advanced")
	void UpdateOnRunEnter();

	UFUNCTION(BlueprintCallable, Category="KerraLocomotion|Advanced")
	void UpdateOnWalkEnter();

	UFUNCTION(BlueprintCallable, Category="KerraLocomotion|Advanced")
	void UpdateRotationWhileMoving(FName CurveName);

	UFUNCTION(BlueprintCallable, Category="KerraLocomotion|Advanced")
	void UpdateLocomotionPlayRate(FName CurveName, float MinRate, float MaxRate);

private:
	UFUNCTION(BlueprintCallable, meta=(BlueprintThreadSafe))
	float GetPredictStopDistance();

protected:
	UPROPERTY()
	AKerraCharacterBase* OwningCharacter;

	UPROPERTY()
	UCharacterMovementComponent* OwningMovementComponent;

	/* Essential Data for Locomotion */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData|Essential")
	bool bHasAcceleration;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData|Essential")
	float GroundSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData|Essential", meta=(ToolTip="[-180, 180]"))
	float LocomotionDirection;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData|Essential")
	FVector Acceleration;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData|Essential")
	FVector Velocity;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData|Essential")
	FVector LastInputVector;

	/* Sub data for Locomotion */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="AnimData|LocomotionData")
	FRotator StartRotation;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="AnimData|LocomotionData")
	FRotator PrimaryRotation;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="AnimData|LocomotionData")
	FRotator SecondaryRotation;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="AnimData|LocomotionData")
	float LocomotionStartAngle;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="AnimData|LocomotionData")
	EKerraLocomotionState LocomotionState;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="AnimData|LocomotionData")
	EKerraMovementStartDirection MovementDirection;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="AnimData|LocomotionData")
	float AnimPlayRate;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="AnimData|LocomotionData")
	float DistanceToMatch;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData|CurveName")
	FName SpeedCurveName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData|CurveName")
	FName RotationCurveName;
};
