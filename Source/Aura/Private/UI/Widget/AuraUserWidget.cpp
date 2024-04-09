// Copyright Paulo R Santos. - Stephen U


#include "UI/Widget/AuraUserWidget.h"

void UAuraUserWidget::SetWidgetController(UObject* InWidgetController)
{
	widgetController = InWidgetController;
	//kick off the the function bellow, witch is blueprint implementable event
	WidgetControllerSet();
}
