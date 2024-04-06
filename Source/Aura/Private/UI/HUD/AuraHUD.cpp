// Copyright Paulo R Santos. - Stephen U


#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if(overlayWidgetController == nullptr)
	{
		overlayWidgetController = NewObject<UOverlayWidgetController>(this, overlayWidgetControllerClass);
		overlayWidgetController->SetWidgetControllerParams(WCParams);
	}

	return overlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{

	checkf(overlayWidgetClass, TEXT("OverlayWidgetclass uninitialized check BP_AuraHud"));
	checkf(overlayWidgetControllerClass, TEXT("OverlayControllerWidgetclass uninitialized check BP_AuraHud"));

	UUserWidget* widget = CreateWidget<UUserWidget>(GetWorld(), overlayWidgetClass);
	overlayWidget = Cast<UAuraUserWidget>(widget);

	const FWidgetControllerParams WCParams(PC, PS, ASC, AS);
	UOverlayWidgetController* widgetController = GetOverlayWidgetController(WCParams);

	overlayWidget->SetWidgetController(overlayWidgetController);

	widget->AddToViewport();
}
