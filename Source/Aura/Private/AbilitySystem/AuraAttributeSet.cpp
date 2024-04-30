// Copyright Paulo R Santos. - Stephen U

#include "AbilitySystem/AuraAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	//Max health and max mana are initialized by game play effect in blueprint
	Inithealth(10.0f);
	Initmana(50.0f);
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Primary
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Strength, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Intelligence, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resilience, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Vigor, COND_None, REPNOTIFY_Always)
	//Secondary
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Armor, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, BlockChance, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitResistence, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always)

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, maxHealth, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, maxMana, COND_None, REPNOTIFY_Always)
	//Vital
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, health, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, mana, COND_None, REPNOTIFY_Always)
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	//HEALTH
	if(GethealthAttribute() == Attribute)
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetmaxHealth());
	}
	//MANA
	if (GetmanaAttribute() == Attribute)
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetmaxMana());
	}
}

void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	//HEALTH
	if (GethealthAttribute() == Data.EvaluatedData.Attribute)
	{
		Sethealth(FMath::Clamp(Gethealth(), 0.0f, GetmaxHealth()));
	}

	//MANA
	if (GetmanaAttribute() == Data.EvaluatedData.Attribute)
	{
		Setmana(FMath::Clamp(Getmana(), 0.0f, GetmaxMana()));
	}
}

/** PRIMARY */
void UAuraAttributeSet::OnRep_Strength(const FGameplayAttributeData& oldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Strength, oldStrength)
}

void UAuraAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& oldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Intelligence, oldIntelligence)
}

void UAuraAttributeSet::OnRep_Resilience(const FGameplayAttributeData& oldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resilience, oldResilience)
}

void UAuraAttributeSet::OnRep_Vigor(const FGameplayAttributeData& oldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Vigor, oldVigor)
}

/** Secondary */
void UAuraAttributeSet::OnRep_Armor(const FGameplayAttributeData& oldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Armor, oldArmor)
}

void UAuraAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& oldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ArmorPenetration, oldArmorPenetration)
}

void UAuraAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& oldBlockChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, BlockChance, oldBlockChance)
}

void UAuraAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& oldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitChance, oldCriticalHitChance)
}

void UAuraAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& oldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitDamage, oldCriticalHitDamage)
}

void UAuraAttributeSet::OnRep_CriticalHitResistence(const FGameplayAttributeData& oldCriticalHitResistence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitResistence, oldCriticalHitResistence)
}

void UAuraAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& oldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, HealthRegeneration, oldHealthRegeneration)
}

void UAuraAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& oldManaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ManaRegeneration, oldManaRegeneration)
}

/** VITAL */
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

void UAuraAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	/**
	 * source = causer of the effect
	 * target = target of the effect (ower of this attributeset) the thing being affected
	 */

	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();

		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}

		if (Props.SourceController != nullptr)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	//TARGET
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Props.TargetController->GetCharacter();
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}

}