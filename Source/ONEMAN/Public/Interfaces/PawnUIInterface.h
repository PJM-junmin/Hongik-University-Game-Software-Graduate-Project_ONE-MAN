// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PawnUIInterface.generated.h"

class UPawnUIComponent;
class UOMPlayerUIComponent;
class UOMEnemyUIComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPawnUIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ONEMAN_API IPawnUIInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UPawnUIComponent* GetPawnUICompoenent() const = 0;
	virtual UOMPlayerUIComponent* GetPlayerUIComponent() const;
	virtual UOMEnemyUIComponent* GetEnemyUIComponent() const;

};
