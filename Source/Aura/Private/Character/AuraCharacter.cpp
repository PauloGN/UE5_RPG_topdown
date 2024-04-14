// Copyright Paulo R Santos. - Stephen U

#include "Character/AuraCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include <Player/AuraPlayerState.h>

#include "AbilitySystemComponent.h"
#include <GameFramework/SpringArmComponent.h>
#include <UI/HUD/AuraHUD.h>

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Player/AuraPlayerController.h"

AAuraCharacter::AAuraCharacter()
{
	UCharacterMovementComponent* cm = GetCharacterMovement();
	cm->bOrientRotationToMovement = true;
	cm->RotationRate = FRotator(0.f, 400.0f, 0.f);
	cm->bConstrainToPlane = true;
	cm->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
	cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	cameraBoom->SetupAttachment(GetMesh());
	cameraBoom->TargetArmLength = 600.0f;
	cameraBoom->bUsePawnControlRotation = true;
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	// Init ability actor info for the Server
	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	// Init ability actor info for the Client
	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	//get player state from PAWN and initialize ability system actor info and then get pointers from there 
	AAuraPlayerState* auraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(auraPlayerState);
	auraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(auraPlayerState, this);
	Cast<UAuraAbilitySystemComponent>(auraPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();

	// Set the pointers
	abilitySystemComponent = auraPlayerState->GetAbilitySystemComponent();
	attributeSet = auraPlayerState->GetAttributeSet();

	if(AAuraPlayerController* auraPlayerController = Cast<AAuraPlayerController>(GetController()))
	{
		if(AAuraHUD* auraHud = Cast<AAuraHUD>(auraPlayerController->GetHUD()))
		{
			auraHud->InitOverlay(auraPlayerController, auraPlayerState, abilitySystemComponent, attributeSet);
		}
	}
}