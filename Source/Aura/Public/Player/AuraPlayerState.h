// Copyright Paulo R Santos. - Stephen U

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	AAuraPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const;

	//Replication
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> abilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> attributeSet;

private:

	UPROPERTY(ReplicatedUsing = OnRep_Level, VisibleAnywhere)
	int32 Level = 1;

	UFUNCTION()
	void OnRep_Level(int32 OldLevel);

};
