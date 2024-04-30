// Copyright Paulo R Santos. - Stephen U

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const;

protected:
	virtual void BeginPlay() override;

	//Member Variables
	UPROPERTY(EditAnywhere, Category = "Combate")
	TObjectPtr<USkeletalMeshComponent> weapon;

#pragma region GAS

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> abilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> attributeSet;

	virtual void InitAbilityActorInfo();

	//Gameplay Effects

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GamePlayEffectClass, float level) const;
	void InitializeDefaultAttributes() const;
#pragma endregion
};