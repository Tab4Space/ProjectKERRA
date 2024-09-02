// Specific for player

#pragma once

#include "CoreMinimal.h"
#include "Animation/Instance/KerraCharacterAnimInstance.h"
#include "KerraHeroAnimInstance.generated.h"


class AKerraHero;

UCLASS()
class KERRA_API UKerraHeroAnimInstance : public UKerraCharacterAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|References")
	AKerraHero* OwningPlayerCharacter;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData")
	bool bShouldEnterRelaxState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData")
	float EnterRelaxStateThreshold = 5.f;

	float  IdleElapsedTime;
};
