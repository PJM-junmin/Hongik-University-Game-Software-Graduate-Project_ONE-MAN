// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/UI/PawnUIComponent.h"
#include "OMEnemyUIComponent.generated.h"

class UOMWidgetBase;

/**
 * 
 */
UCLASS()
class ONEMAN_API UOMEnemyUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void RegisterEnemyDrawnWidget(UOMWidgetBase* inWidgetToRegister);

	UFUNCTION(BlueprintCallable)
	void RemoveEnemyDrawnWidgetsIfAny();

private:
	TArray<UOMWidgetBase*> enemyDrawnWidgets;
};
