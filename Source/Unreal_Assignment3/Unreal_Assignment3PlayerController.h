// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Unreal_Assignment3PlayerController.generated.h"

UCLASS()
class AUnreal_Assignment3PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AUnreal_Assignment3PlayerController();


protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	/** Shooting Projectiles. */
	void OnShoot();

	/** Losing HP. */
	void LoseHP();

	/** Shooting AOE Bombs. */
	void onAOE();

	//#### Action to open Lootbox
	void OnAction();

	//#### Callback when drinking the HPPotion
	void OnHPPotion();

	//#### Callback when drinking the MPPotion
	void OnManaPotion();

	//#### Callback when drinking the SpeedPotion
	void OnSpeedPotion();
};


