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