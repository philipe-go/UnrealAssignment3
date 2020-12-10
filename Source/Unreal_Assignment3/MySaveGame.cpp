// Fill out your copyright notice in the Description page of Project Settings.


#include "Unreal_Assignment3.h"
#include "MySaveGame.h"

UMySaveGame::UMySaveGame()
{
	SaveSlotName = TEXT("0");
	UserIndex = 0;
	PlayerTransform = FTransform::Identity;
	HPPotions = 0;
	ManaPotions = 0;
	SpeedPotions = 0;
}


