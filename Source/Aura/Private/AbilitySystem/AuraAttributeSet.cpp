// Copyright Paulo R Santos. - Stephen U


#include "AbilitySystem/AuraAttributeSet.h"
#include "Net/UnrealNetwork.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	Inithealth(25);
	InitmaxHealth(100);
	Initmana(100);
	InitmaxMana(100.0f);
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, health, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, maxHealth, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, mana, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, maxMana, COND_None, REPNOTIFY_Always)

}

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& oldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, health, oldHealth)
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& oldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, maxHealth, oldMaxHealth)
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& oldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, mana, oldMana)
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData & oldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, maxMana, oldMaxMana)
}
