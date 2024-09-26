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

protected:
	UFUNCTION(BlueprintCallable, Category="Locomotion|Advanced")
	void FindLocomotionState();

	UFUNCTION(BlueprintCallable, Category="Locomotion|Advanced")
	void FindLocomotionStartDirection();

	UFUNCTION(BlueprintCallable, Category="Locomotion|Advanced")
	void UpdateOnRunEnter();

	UFUNCTION(BlueprintCallable, Category="Locomotion|Advanced")
	void UpdateOnWalkEnter();

	UFUNCTION(BlueprintCallable, Category="Locomotion|Advanced")
	void UpdateRotationWhileMoving();

	UFUNCTION(BlueprintCallable, Category="Locomotion|Advanced")
	void UpdateLocomotionPlayRate();

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
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="AnimData|LocomotionData|Advanced")
	FRotator StartRotator;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="AnimData|LocomotionData|Advanced")
	FRotator PrimaryRotation;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="AnimData|LocomotionData|Advanced")
	FRotator SecondaryRotation;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="AnimData|LocomotionData|Advanced")
	float LocomotionStartAngle;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="AnimData|LocomotionData|Advanced")
	EKerraLocomotionState LocomotionState;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="AnimData|LocomotionData|Advanced")
	EKerraMovementStartDirection MovementDirection;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="AnimData|LocomotionData|Advanced")
	float AnimPlayRate;
};
