// Specific for player

#pragma once

#include "CoreMinimal.h"
#include "Animation/Instance/KerraCharacterAnimInstance.h"
#include "KerraPlayerAnimInstance.generated.h"


class AKerraPlayer;

UCLASS()
class KERRA_API UKerraPlayerAnimInstance : public UKerraCharacterAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|References")
	AKerraPlayer* OwningPlayerCharacter;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData")
	bool bShouldEnterRelaxState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData")
	float EnterRelaxStateThreshold = 5.f;

	float  IdleElapsedTime;
};
