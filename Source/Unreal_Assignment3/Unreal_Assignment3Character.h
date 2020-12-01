// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Unreal_Assignment3Character.generated.h"

UCLASS(Blueprintable)
class AUnreal_Assignment3Character : public ACharacter
{
	GENERATED_BODY()

public:
	AUnreal_Assignment3Character();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	/** This is for the projectile **/
	UPROPERTY(VisibleAnywhere)
	USceneComponent* ProjectileOrigin;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileActor;

	void Shoot();

	UFUNCTION(BlueprintImplementableEvent)
		void ShootAnim();

	/** This is for the AOE  **/
	UPROPERTY(VisibleAnywhere)
		USceneComponent* AOEOrigin;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> AOEActor;

	void AOE();

	/** Player Health **/
	UPROPERTY(BlueprintReadWrite)
	float HP = 1.0f;

	/** Player MANA **/
	UPROPERTY(BlueprintReadOnly)
	float Mana = 1.0f;


	

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;


	
};

