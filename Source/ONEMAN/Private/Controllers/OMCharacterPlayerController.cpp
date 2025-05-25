// Vince Petrelli all Rights Reserved


#include "Controllers/OMCharacterPlayerController.h"

AOMCharacterPlayerController::AOMCharacterPlayerController()
{
	PlayerTeamID = FGenericTeamId(0);
}

FGenericTeamId AOMCharacterPlayerController::GetGenericTeamId() const
{
	return PlayerTeamID;
}
