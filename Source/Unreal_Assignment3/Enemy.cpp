// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemy::OnHit()
{
	HitValue = 1;
    
	// When the enemy gets hit, he loses 10%
	Enemy_HP -= 0.1f;

	GEngine->AddOnScreenDebugMessage(0, 2, FColor::Red, TEXT("Enemy is HIT"));
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	HitValue -= DeltaTime;
	if (HitValue < 0)
	{
		HitValue = 0;
	}
	SkeletalMesh->SetScalarParameterValueOnMaterials(TEXT("Hit"), HitValue);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



