#pragma once

UENUM()
enum class EKerraConfirmType : uint8
{
	Yes,
	No
};

UENUM()
enum class EKerraValidType : uint8
{
	Valid,
	Invalid
};

UENUM()
enum class EKerraSuccessType : uint8
{
	Successful,
	Fail
};

UENUM()
enum class EKerraCountDownActionInput : uint8
{
	Start,
	Cancel,
};

UENUM()
enum class EKerraCountDownOutput : uint8
{
	Updated,
	Completed,
	Cancel
};

UENUM(BlueprintType)
enum class EKerraLocomotionState : uint8
{
	Idle,
	Walk,
	Run
};

UENUM(BlueprintType)
enum class EKerraMovementStartDirection : uint8
{
	Forward,
	Right,
	Left,
	BackRight,
	BackLeft
};

UENUM(BlueprintType)
enum class EKerraParkourType : uint8
{
	None,
	Hurdle,
	Vault,
	Mantle
};