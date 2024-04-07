// Copyright Paulo R Santos. - Stephen U


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadCastInitialValues()
{
	const UAuraAttributeSet* AAS = CastChecked<UAuraAttributeSet>(attributeSet);

	const float health = AAS->Gethealth();
	const float maxHealth = AAS->GetmaxHealth();

	OnHealthChanged.Broadcast(health);
	OnMaxHealthChanged.Broadcast(maxHealth);
}
