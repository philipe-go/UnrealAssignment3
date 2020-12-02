// Fill out your copyright notice in the Description page of Project Settings.

#include "Potion.h"
#include "Unreal_Assignment3Character.h"

APotion::APotion()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	MeshComponent->SetCanEverAffectNavigation(false);
}

void APotion::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	AUnreal_Assignment3Character* MyPlayer = Cast<AUnreal_Assignment3Character>(OtherActor);
	if (MyPlayer)
	{
		switch (PotionType)
		{
		case 0:
		{
			MyPlayer->HPPotions++;
		}break;
		case 1:
		{
			MyPlayer->ManaPotions++;
		}break;
		case 2:
		{
			MyPlayer->SpeedPotions++;
		}break;
		default:
		{
			MyPlayer->HPPotions++;
		}break;
		}
		
		Destroy();
	}
}




