// Copyright Paulo R Santos. - Stephen U


#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* widget = CreateWidget<UUserWidget>(GetWorld(), overlayWidgetClass);
	widget->AddToViewport();

}
