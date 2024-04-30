// Copyright Paulo R Santos. - Stephen U


#include "Character/AuraCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"

AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return abilitySystemComponent;
}

UAttributeSet* AAuraCharacterBase::GetAttributeSet() const
{
	return attributeSet;
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	
}

void AAuraCharacterBase::InitAbilityActorInfo()
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1);
}

void AAuraCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GamePlayEffectClass, float level) const
{
	check(GetAbilitySystemComponent());
	check(GamePlayEffectClass);

	const FGameplayEffectContextHandle GPE_ContexHandle = GetAbilitySystemComponent()->MakeEffectContext();
	const FGameplayEffectSpecHandle GPE_SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GamePlayEffectClass, level, GPE_ContexHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*GPE_SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void AAuraCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.0f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.0f);
}
