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
	abilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AAS->GethealthAttribute()).AddUObject(this, &ThisClass::HealthChanged);
	abilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AAS->GetmaxHealthAttribute()).AddUObject(this, &ThisClass::MaxHealthChanged);
	//Mana
	abilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AAS->GetmanaAttribute()).AddUObject(this, &ThisClass::ManaChanged);
	abilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AAS->GetmaxManaAttribute()).AddUObject(this, &ThisClass::MaxManaChanged);
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

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
