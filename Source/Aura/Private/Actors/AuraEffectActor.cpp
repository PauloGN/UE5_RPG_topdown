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
	const FActiveGameplayEffectHandle ActiveEffectHandle =  TargetASC->ApplyGameplayEffectSpecToSelf(*Gpes_Handle.Data.Get());

	//gameplay effect spec/ ugameplay effect/
	const bool bIsInfinite = Gpes_Handle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if(bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
	}
}

void AAuraEffectActor::OnOverlap(AActor* OverlappedActor)
{
    if(InstantEffectAplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
    {
		ApplyEffectToTarget(OverlappedActor, InstantGameplayEffectClass);
    }

	if (DurationEffectAplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(OverlappedActor, DurationGameplayEffectClass);
	}

	if (InfiniteEffectAplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(OverlappedActor, InfiniteGameplayEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* OverlappedActor)
{
	if (InstantEffectAplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(OverlappedActor, InstantGameplayEffectClass);
	}

	if (DurationEffectAplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(OverlappedActor, DurationGameplayEffectClass);
	}

	if (InfiniteEffectAplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(OverlappedActor, InfiniteGameplayEffectClass);
	}

	if(InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OverlappedActor);
		if(!IsValid(TargetASC))
		{
			return;
		}

		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		for(TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair : ActiveEffectHandles)
		{
			if(TargetASC == HandlePair.Value)
			{
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key);
				HandlesToRemove.Add(HandlePair.Key);
			}
		}

		for (FActiveGameplayEffectHandle& ToRemove : HandlesToRemove)
		{
			ActiveEffectHandles.FindAndRemoveChecked(ToRemove);
		}
	}
}
