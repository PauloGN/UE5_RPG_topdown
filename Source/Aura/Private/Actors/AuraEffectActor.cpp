// Copyright Paulo R Santos. - Stephen U

#include "Actors/AuraEffectActor.h"
#include "AbilitySystemComponent.h"
#include <AbilitySystemBlueprintLibrary.h>

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot")));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	if(TargetASC == nullptr)
	{
		return;
	}
	check(GameplayEffectClass);

	FGameplayEffectContextHandle Gpec_Handle = TargetASC->MakeEffectContext();
	Gpec_Handle.AddSourceObject(this);
	const FGameplayEffectSpecHandle Gpes_Handle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.0f, Gpec_Handle);
	TargetASC->ApplyGameplayEffectSpecToSelf(*Gpes_Handle.Data.Get());
}
