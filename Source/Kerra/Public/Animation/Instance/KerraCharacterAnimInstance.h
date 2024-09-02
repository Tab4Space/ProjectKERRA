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
	float GroundSpeed;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData")
	bool bHasAcceleration;
};
