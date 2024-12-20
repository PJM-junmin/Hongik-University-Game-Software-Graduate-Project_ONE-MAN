// Vince Petrelli all Rights Reserved


#include "Widgets/OMWidgetBase.h"
#include "Interfaces/PawnUIInterface.h"
#include "Components/UI/OMEnemyUIComponent.h"

void UOMWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(GetOwningPlayerPawn());

	if(PawnUIInterface)
	{
		if (UOMPlayerUIComponent* PlayerUIComponent = PawnUIInterface->GetPlayerUIComponent())
		{
			BP_OnOwningPlayerUIComponentInitialized(PlayerUIComponent);
		}
	}
}

void UOMWidgetBase::InitEnemyCreatedWidget(AActor* OwningEnemyActor)
{
	IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(OwningEnemyActor);

	if (PawnUIInterface)
	{
		UOMEnemyUIComponent* EnemyUIComponent = PawnUIInterface->GetEnemyUIComponent();

		checkf(EnemyUIComponent, TEXT("Failed to extrac an EnemyUIComponent from %s"), *OwningEnemyActor->GetActorNameOrLabel());

		BP_OnOwningEnemyUIComponentInitialized(EnemyUIComponent);
	}
}
