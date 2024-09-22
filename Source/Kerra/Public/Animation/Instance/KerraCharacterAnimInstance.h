// Anim Instance for player and enemy
// Shared by player and enemy

#pragma once

#include "CoreMinimal.h"
#include "Animation/Instance/KerraAnimInstanceBase.h"
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
	UPROPERTY()
	AKerraCharacterBase* OwningCharacter;

	UPROPERTY()
	UCharacterMovementComponent* OwningMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData")
	bool bHasAcceleration;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData")
	float GroundSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData", meta=(ToolTip="[-180, 180]"))
	float LocomotionDirection;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData|Advanced")
	float LocomotionStartAngle;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData|Advanced")
	FVector Acceleration;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData|Advanced")
	FVector Velocity;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData|Advanced")
	FVector LastInputVector;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData|Advanced")
	FRotator StartRotator;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData|Advanced")
	FRotator PrimaryRotation;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData|Advanced")
	FRotator SecondaryRotation;

};
