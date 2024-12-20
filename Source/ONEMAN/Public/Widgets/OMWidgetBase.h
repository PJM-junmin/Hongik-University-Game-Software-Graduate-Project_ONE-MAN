// Vince Petrelli all Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OMWidgetBase.generated.h"

class UOMPlayerUIComponent;
class UOMEnemyUIComponent;

/**
 * 
 */
UCLASS()
class ONEMAN_API UOMWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Owning PlayerUIComponentInitialized"))
	void BP_OnOwningPlayerUIComponentInitialized(UOMPlayerUIComponent* OwningPlayerUIComponent);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Owning EnemyUIComponentInitialized"))
	void BP_OnOwningEnemyUIComponentInitialized(UOMEnemyUIComponent* OwningEnemyUIComponent);

public:
	// CallBack Function
	UFUNCTION(BlueprintCallable)
	void InitEnemyCreatedWidget(AActor* OwningEnemyActor);

};
