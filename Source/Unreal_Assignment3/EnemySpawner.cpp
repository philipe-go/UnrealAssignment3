// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemySpawner.h"
#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"
#include "Unreal_Assignment3Character.h"
#include "Enemy.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	//### Initialize the Static Mesh Component
	TrapMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Trap Mesh"));
	TrapMesh->SetupAttachment(RootComponent);

	//### Trigger area initialization
	TriggerArea = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger Area"));
	TriggerArea->AttachToComponent(TrapMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	TriggerArea->InitSphereRadius(SpawnRadius);

	//### Delegate to start Overlap event when triggered
	TriggerArea->OnComponentBeginOverlap.AddDynamic(this, &AEnemySpawner::OnOverlapBegin);
}

void AEnemySpawner::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AUnreal_Assignment3Character* MyPlayer = Cast<AUnreal_Assignment3Character>(OtherActor);
	if (MyPlayer)
	{
		SpawnEnemies(MyPlayer);
	}
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemySpawner::SpawnEnemies(AActor* MyPlayer)
{
	FVector Location;
	const FRotator Rotation = FRotator::ZeroRotator;

	//### Move Spawn Area to center of trap
	SpawnBounds.Min = GetActorLocation();
	SpawnBounds.Max = FVector(SpawnBounds.GetCenter().X + SpawnRadius, SpawnBounds.GetCenter().Y + SpawnRadius, 0);
	DrawDebugBox(GetWorld(), SpawnBounds.Min, SpawnBounds.Max, FColor::Red, false, 5, -1, 2);

	while (SpawnAmount > 0)
	{
		Location = FMath::RandPointInBox(SpawnBounds);
		Location.Z = GetActorLocation().Z;
		OnEnemySpawn(Location, Rotation); 
		AEnemy* NewEnemy = GetWorld()->SpawnActor<AEnemy>(EnemyToSpawn, Location, Rotation);

		SpawnAmount--;
	}
	this->Destroy();
}

