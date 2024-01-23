// Copyright Paulo R Santos. - Stephen U


#include "Character/AuraCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

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

}
