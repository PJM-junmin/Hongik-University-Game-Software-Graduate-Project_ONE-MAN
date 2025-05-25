// Vince Petrelli all Rights Reserved


#include "Components/UI/OMEnemyUIComponent.h"
#include "Widgets/OMWidgetBase.h"

void UOMEnemyUIComponent::RegisterEnemyDrawnWidget(UOMWidgetBase* inWidgetToRegister)
{
	enemyDrawnWidgets.Add(inWidgetToRegister);
}

void UOMEnemyUIComponent::RemoveEnemyDrawnWidgetsIfAny()
{
	if (enemyDrawnWidgets.IsEmpty())
		return;

	for (UOMWidgetBase* drawnWidget : enemyDrawnWidgets)
	{
		if (drawnWidget)
		{
			drawnWidget->RemoveFromParent();
		}
	}

	enemyDrawnWidgets.Empty();
}
