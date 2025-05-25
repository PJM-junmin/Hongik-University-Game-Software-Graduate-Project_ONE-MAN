// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Types/OMEnumTypes.h"
#include "OMGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ONEMAN_API AOMGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AOMGameModeBase();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Settings")
	EOMGameDifficulty currentGameDifficulty;

public:
	FORCEINLINE EOMGameDifficulty GetCurrentGameDifficulty() const { return currentGameDifficulty; }

};
