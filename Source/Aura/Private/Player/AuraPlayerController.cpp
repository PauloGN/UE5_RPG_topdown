// Copyright Paulo R Santos. - Stephen U

#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Character/AuraCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interaction/EnemyInterface.h"

namespace 
{
	constexpr float MAX_ARM_LENGTH = 700.0f;
	constexpr float MIN_ARM_LENGTH = 150.0f;
	constexpr float ARM_LENGTH_RATE = 10.0f;
}

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaSeconds)
{
	Super::PlayerTick(DeltaSeconds);

	if(bShowMouseCursor)
	{
		CursorTrace();
	}
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(auraContext);

	UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if(subsystem)
	{
		subsystem->AddMappingContext(auraContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI inputModeData;
	inputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	inputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(inputModeData);

	//Get USpringArm Comp
	// Get a reference to the character
	AAuraCharacter* AuraChar = Cast<AAuraCharacter>(GetPawn());

	if (AuraChar)
	{
		// Access the SpringArm component
		USpringArmComponent* SpringArm = AuraChar->FindComponentByClass<USpringArmComponent>();
		if (SpringArm)
		{
			cameraBoom = SpringArm;
		}
	}
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	enhancedInputComponent->BindAction(moveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	enhancedInputComponent->BindAction(lookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
	enhancedInputComponent->BindAction(allowCameraAction, ETriggerEvent::Triggered, this, &ThisClass::AllowCameraMove);
	enhancedInputComponent->BindAction(allowCameraAction, ETriggerEvent::Completed, this, &ThisClass::AllowCameraMove);
	enhancedInputComponent->BindAction(zoomIn, ETriggerEvent::Triggered, this, &ThisClass::ZoomInFun);
	enhancedInputComponent->BindAction(zoomOut, ETriggerEvent::Triggered, this, &ThisClass::ZoomOutFun);
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

void AAuraPlayerController::Look(const FInputActionValue& InputActionValue)
{
	if(!bAllowCameraAction)
	{
		return;
	}

	// Get the input values
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	// Get the controlled pawn (assuming it's the character)
	APawn* ControlledPawn = GetPawn();

	// Check if the controlled pawn exists and is of type AAuraCharacter
	if (ControlledPawn && ControlledPawn->IsA<AAuraCharacter>())
	{
		//Note: To control camera rotation SpringAmr should activate usePawnControlRotation as well inherit pitch, roll and yaw
		ControlledPawn->AddControllerYawInput(LookAxisVector.X);
		ControlledPawn->AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AAuraPlayerController::AllowCameraMove(const FInputActionValue& InputActionValue)
{
	bAllowCameraAction = InputActionValue.Get<bool>();

	if(bAllowCameraAction)
	{
		bShowMouseCursor = false;
		GEngine->AddOnScreenDebugMessage(1, 10, FColor::Blue, "Down");
		FInputModeGameOnly gameInput;
		gameInput.SetConsumeCaptureMouseDown(true);
		SetInputMode(gameInput);
	}else
	{
		GEngine->AddOnScreenDebugMessage(1, 10, FColor::Blue, "Up");
		bShowMouseCursor = true;
		DefaultMouseCursor = EMouseCursor::Default;

		FInputModeGameAndUI inputModeData;

		inputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		inputModeData.SetHideCursorDuringCapture(false);
		SetInputMode(inputModeData);
	}
}

void AAuraPlayerController::ZoomInFun(const FInputActionValue& InputActionValue)
{
	cameraBoom->TargetArmLength -= ARM_LENGTH_RATE;
	if (cameraBoom->TargetArmLength <= MIN_ARM_LENGTH)
	{
		cameraBoom->TargetArmLength = MIN_ARM_LENGTH;
	}
}

void AAuraPlayerController::ZoomOutFun(const FInputActionValue& InputActionValue)
{
	cameraBoom->TargetArmLength += ARM_LENGTH_RATE;
	if (cameraBoom->TargetArmLength >= MAX_ARM_LENGTH)
	{
		cameraBoom->TargetArmLength = MAX_ARM_LENGTH;
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
