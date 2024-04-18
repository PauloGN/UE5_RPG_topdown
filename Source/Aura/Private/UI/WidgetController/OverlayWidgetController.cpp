// Copyright Paulo R Santos. - Stephen U

#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadCastInitialValues()
{
	const UAuraAttributeSet* AAS = CastChecked<UAuraAttributeSet>(attributeSet);

	const float health = AAS->Gethealth();
	const float maxHealth = AAS->GetmaxHealth();
	const float mana = AAS->Getmana();
	const float maxMana = AAS->GetmaxMana();

	OnHealthChanged.Broadcast(health);
	OnMaxHealthChanged.Broadcast(maxHealth);

	OnManaChanged.Broadcast(mana);
	OnMaxManaChanged.Broadcast(maxMana);
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAuraAttributeSet* AAS = CastChecked<UAuraAttributeSet>(attributeSet);

	//health
	abilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AAS->GethealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);

	abilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AAS->GetmaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);
	//Mana
	abilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AAS->GetmanaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}
	);

	abilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AAS->GetmaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		}
	);
	//AuraAbilitySystemComponent
	Cast<UAuraAbilitySystemComponent>(abilitySystemComponent)->EffectAssetTags_Delegate.AddLambda(
		[this](const FGameplayTagContainer& TagContainer)
		{
			for (const FGameplayTag& tag : TagContainer)
			{
				//For example, say that Tag = Message.HealthPotion
				//Message.HealthPotion.MatchesTag("Message") => true | Message.MatchesTag("Message.HealthPotion") => false;
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));

				if(tag.MatchesTag(MessageTag))
				{
					const FUIWidgetRow* Row =  GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, tag);
					MessageWidgetRowSignature_Delegate.Broadcast(*Row);
				}
			}
		}
	);
}
