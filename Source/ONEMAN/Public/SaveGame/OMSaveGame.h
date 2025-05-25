// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Types/OMEnumTypes.h"
#include "OMSaveGame.generated.h"


/**
 * 
 */
UCLASS()
class ONEMAN_API UOMSaveGame : public USaveGame
{
	GENERATED_BODY()
	

public:
	UPROPERTY(BlueprintReadOnly)
	EOMGameDifficulty savedCurrentGameDifficulty;

};
