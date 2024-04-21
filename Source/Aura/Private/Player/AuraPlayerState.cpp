// Copyright Paulo R Santos. - Stephen U


#include "Player/AuraPlayerState.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

AAuraPlayerState::AAuraPlayerState()
{
	abilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	abilitySystemComponent->SetIsReplicated(true);
	//Sets how game play effects will be replicated to clients
	abilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	attributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	//How often the server will try to update clients
	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return abilitySystemComponent;
}

UAttributeSet* AAuraPlayerState::GetAttributeSet() const
{
	return attributeSet;
}
