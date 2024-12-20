// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "Types/OMStructTypes.h"
#include "DataAsset_PlayerStartUpData.generated.h"


/**
 * 
 */
UCLASS()
class ONEMAN_API UDataAsset_PlayerStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()
	
public:
	// Apply Ability to Character or Object, and You can exert the Abilitys to control the extent of the effects.
	virtual void GiveToAbilitySystemComponent(UOMAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta = (TitleProperty = "InputTag"))
	TArray<FOMPlayerAbilitySet> PlayerStartUpAbilitySets;
};
