// Copyright Paulo R Santos. - Stephen U

#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaSeconds)
{
	Super::PlayerTick(DeltaSeconds);

	CursorTrace();

}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(auraContext);

	UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(subsystem);

	subsystem->AddMappingContext(auraContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI inputModeData;

	inputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	inputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(inputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	enhancedInputComponent->BindAction(moveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAAxisVector = InputActionValue.Get<FVector2D>();

	const FRotator rotation = GetControlRotation();
	const FRotator yawRotation (0.0f, rotation.Yaw, 0.0f);

	const FVector forwardDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	const FVector rightdDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

	if(APawn* controlledPawn = GetPawn<APawn>())
	{
		controlledPawn->AddMovementInput(forwardDirection, InputAAxisVector.Y);
		controlledPawn->AddMovementInput(rightdDirection, InputAAxisVector.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult cursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, cursorHit);

	if(!cursorHit.bBlockingHit)
	{
		return;
	}

	lastActor = thisActor;
	thisActor = Cast<IEnemyInterface>(cursorHit.GetActor());

	/**
	 *	Line trace from cursor. There are several scenarios
	 *	A. Last actor is null and this actor is null
	 *		- Do nothing
	 *	B. LastActor is null && thisAcor  is valid
	 *		- Highlight thisActor
	 *	C. lastActor is valid && thisActor is null
	 *		- UnHighlight lastActor
	 *	D. Both actors are Valid, but lastActor != thisActor
	 * 		- UnHighlight lastActor, and Highlight thisActor
	 *	E. Both actors are Valid, and lastActor == thisActor
	 *		- Do nothing
	 */

	if(lastActor == nullptr)
	{
		if(thisActor != nullptr)
		{
			//case b
			thisActor->HighlightActor();

		}else
		{
			//case a

		}
	}else
	{
		if (thisActor == nullptr)
		{
			//case c
			lastActor->UnHighlightActor();

		}else//both valid
		{
			if(lastActor != thisActor)
			{
				//case d
				lastActor->UnHighlightActor();
				thisActor->HighlightActor();
			}else
			{
				//case E do nothing
			}
		}
	}
}
