// Copyright Paulo R Santos. - Stephen U

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AAuraPlayerController();

	virtual void PlayerTick(float DeltaSeconds) override;

protected:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:

#pragma region INPUTS

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> auraContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> moveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> lookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> allowCameraAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> zoomIn;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> zoomOut;

	void Move(const FInputActionValue& InputActionValue);
	void Look(const FInputActionValue& InputActionValue);
	void AllowCameraMove(const FInputActionValue& InputActionValue);

	void ZoomInFun(const FInputActionValue& InputActionValue);
	void ZoomOutFun(const FInputActionValue& InputActionValue);
#pragma endregion

	void CursorTrace();
	IEnemyInterface* lastActor;
	IEnemyInterface* thisActor;

	bool bAllowCameraAction = false;

	TObjectPtr<class USpringArmComponent> cameraBoom;

};