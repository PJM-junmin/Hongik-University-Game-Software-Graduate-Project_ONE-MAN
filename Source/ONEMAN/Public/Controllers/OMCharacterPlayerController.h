// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "OMCharacterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ONEMAN_API AOMCharacterPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
public:
	AOMCharacterPlayerController();
	virtual FGenericTeamId GetGenericTeamId() const override;

private:
	FGenericTeamId PlayerTeamID;
};
