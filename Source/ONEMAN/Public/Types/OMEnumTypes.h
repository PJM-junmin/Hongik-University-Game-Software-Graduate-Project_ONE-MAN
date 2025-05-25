#pragma once
UENUM()
enum class EOMConfirmType : uint8
{
	Yes,
	No,
};

UENUM()
enum class EOMValidType : uint8
{
	Valid,
	InValid,
};

UENUM()
enum class EOMSuccessType : uint8
{
	Successful,
	Failed,
};

UENUM()
enum class EOMCountDownActionInput : uint8
{
	Start,
	Cancel,
};

UENUM()
enum class EOMCountDownActionOutput : uint8
{
	Updated,
	Completed,
	Cancelled,
};

UENUM(BlueprintType)
enum class EOMGameDifficulty : uint8
{
	Easy,
	Normal,
	Hard,
	Impossible
};

UENUM()
enum class EOMInputMode : uint8
{
	GameOnly,
	UIOnly,
};