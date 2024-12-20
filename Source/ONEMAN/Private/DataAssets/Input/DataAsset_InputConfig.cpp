// Vince Petrelli all Rights Reserved


#include "DataAssets/Input/DataAsset_InputConfig.h"

UInputAction* UDataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
	for (const FOMInputActionConfig& InputActionConfig : NativeInputActions) /* Read Only */
	{
		if (InputActionConfig.InputTag == InInputTag && InputActionConfig.InputAction != nullptr)
		{
			return InputActionConfig.InputAction;
		}
	}

	return nullptr;
}
