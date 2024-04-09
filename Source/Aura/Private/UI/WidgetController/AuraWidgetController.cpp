// Copyright Paulo R Santos. - Stephen U


#include "UI/WidgetController/AuraWidgetController.h"

void UAuraWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	playerController = WCParams.playerController;
	playerState = WCParams.playerState;
	attributeSet = WCParams.attributeSet;
	abilitySystemComponent = WCParams.abilitySystemComponent;
}

void UAuraWidgetController::BroadCastInitialValues()
{
}

void UAuraWidgetController::BindCallbacksToDependencies()
{
}
