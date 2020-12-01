// Fill out your copyright notice in the Description page of Project Settings.


#include "Lootbox.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ALootbox::ALootbox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// if we make a Mesh in .h , we have to make a component in .cpp
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ALootbox::BeginPlay()
{
	Super::BeginPlay();

	// Gets a random Num when Lootbox is Opened!
	RandomNum = FMath::RandRange(0, 9);
	OpenLoot();
}

// Called every frame
void ALootbox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ALootbox::OpenLoot()
{
	// 60% chance you get HEALTH potion
	if (RandomNum < 5)
	{
		GEngine->AddOnScreenDebugMessage(0, 2, FColor::Red, TEXT("Health Potion!"));
	} 
	// 30% chance you get MANA potion
	else if (RandomNum >= 6 && RandomNum < 9)
	{
		GEngine->AddOnScreenDebugMessage(0, 2, FColor::Blue, TEXT("Mana Potion!"));
	}
	// 10% chance you get SPEED potion
	else if (RandomNum == 9)
	{
		GEngine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Speed Potion!"));
	}
	
	//UE_LOG(LogTemp, Warning, TEXT("Loot num: "), RandomNum);
}

