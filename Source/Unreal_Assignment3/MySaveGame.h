// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

/**
 *
 */
UCLASS()
class UNREAL_ASSIGNMENT3_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		uint32 UserIndex;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FTransform PlayerTransform;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		float PlayerHP;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		float PlayerMP;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		int HPPotions;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		int ManaPotions;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		int SpeedPotions;

	UMySaveGame();
};
