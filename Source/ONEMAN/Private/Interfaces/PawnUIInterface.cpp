// Vince Petrelli all Rights Reserved


#include "Interfaces/PawnUIInterface.h"

// Add default functionality here for any IPawnUIInterface functions that are not pure virtual.
UOMPlayerUIComponent* IPawnUIInterface::GetPlayerUIComponent() const
{
	return nullptr;
}

UOMEnemyUIComponent* IPawnUIInterface::GetEnemyUIComponent() const
{
	return nullptr;
}
