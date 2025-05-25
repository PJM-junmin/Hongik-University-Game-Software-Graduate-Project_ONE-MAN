#pragma once
#include "CoreMinimal.h"

	UENUM(BlueprintType)
		enum class EPlayerNativeState :uint8
	{
		Idle,
		Walk,
		Sprint,
	};
