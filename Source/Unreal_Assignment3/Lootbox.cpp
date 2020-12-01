// Fill out your copyright notice in the Description page of Project Settings.

#include "Lootbox.h"
#include "Components/SphereComponent.h"
#include "Unreal_Assignment3Character.h"
#include "Unreal_Assignment3PlayerController.h"
#include "Potion.h"
#include "Math/UnrealMathUtility.h"

ALootbox::ALootbox()
{
	PrimaryActorTick.bCanEverTick = true;

	// if we make a Mesh in .h , we have to make a component in .cpp
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	TriggerArea = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger Area"));
	TriggerArea->InitSphereRadius(300);
	TriggerArea->SetGenerateOverlapEvents(true);
	TriggerArea->SetupAttachment(RootComponent);

	//### Assign the Overlap methods to the framework events
	TriggerArea->OnComponentBeginOverlap.AddDynamic(this, &ALootbox::OnOverlapBegin);
	TriggerArea->OnComponentEndOverlap.AddDynamic(this, &ALootbox::OnOverlapEnd);
}

void ALootbox::BeginPlay()
{
	Super::BeginPlay();
}

void ALootbox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALootbox::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AUnreal_Assignment3Character* MyPlayer = Cast<AUnreal_Assignment3Character>(OtherActor);
	if (MyPlayer)
	{
		//bPlayerClose = true;
		MyPlayer->OnActionReceiver = this;
		GEngine->AddOnScreenDebugMessage(0, 2, FColor::Red, TEXT("Player is Close!"));
	}
}

void ALootbox::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AUnreal_Assignment3Character* MyPlayer = Cast<AUnreal_Assignment3Character>(OtherActor);
	if (MyPlayer)
	{
		//bPlayerClose = false;
		MyPlayer->OnActionReceiver = nullptr;
		GEngine->AddOnScreenDebugMessage(0, 2, FColor::Red, TEXT("Player is Away!"));
	}
}

void ALootbox::OpenLoot()
{
	// Gets a random Num when Lootbox is Opened!
	RandomNum = FMath::RandRange(0, 9);

		// 60% chance you get HEALTH potion
		if (RandomNum < 5)
		{
			GEngine->AddOnScreenDebugMessage(0, 2, FColor::Red, TEXT("Health Potion!"));
			APotion* MyPotion = GetWorld()->SpawnActor<APotion>(HealthPotion, GetActorLocation(), GetActorRotation());
		}
		// 30% chance you get MANA potion
		else if (RandomNum >= 6 && RandomNum < 9)
		{
			GEngine->AddOnScreenDebugMessage(0, 2, FColor::Blue, TEXT("Mana Potion!"));
			APotion* MyPotion = GetWorld()->SpawnActor<APotion>(ManaPotion, GetActorLocation(), GetActorRotation());
		}
		// 10% chance you get SPEED potion
		else if (RandomNum == 9)
		{
			GEngine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Speed Potion!"));
			APotion* MyPotion = GetWorld()->SpawnActor<APotion>(SpeedPotion, GetActorLocation(), GetActorRotation());
		}

		OnLootOpen(GetActorLocation(), GetActorRotation());
		Destroy();

	//UE_LOG(LogTemp, Warning, TEXT("Loot num: "), RandomNum);
}

