// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomb.h"
#include "Enemy.h"
#include "Unreal_Assignment3Character.h"
#include "Unreal_Assignment3PlayerController.h"
#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "TimerManager.h"

// Sets default values
ABomb::ABomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// if we make a Mesh in .h , we have to make a component in .cpp
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	//for the sphere overlap size
	SphereRadius = 100.0f;

	MyCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("My Sphere Component"));
	MyCollisionSphere->InitSphereRadius(SphereRadius);
	//MyCollisionSphere->SetCollisionProfileName("Trigger");
	RootComponent = MyCollisionSphere;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My MESH"));
	MyMesh->SetupAttachment(RootComponent);

	// Use this component to drive this projectile's movement.
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(MyCollisionSphere);
	ProjectileMovementComponent->InitialSpeed = 1500.0f;
	ProjectileMovementComponent->MaxSpeed = 1500.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;

	MyCollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABomb::OnSphereOverlapBegin);
}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();

	// 5 seconds count down before the aoe bomb gets destroyed
	GetWorld()->GetTimerManager().SetTimer(removeBomb, this, &ABomb::NoBomb, 5.f, false);
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawDebugSphere(GetWorld(), GetActorLocation(), SphereRadius, 10, FColor::Purple, false, -1, 0, 1);
}

//Regular Overlay
void ABomb::NotifyActorBeginOverlap(AActor* OtherActor)
{
	//ADD "#include "Unreal_Assignment3Character.h"" on top

	//AUnreal_Assignment3Character* Player = Cast<AUnreal_Assignment3Character>(OtherActor);

	//FVector PlayerPos = Player->GetActorLocation();

	//TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;
	//TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	//TArray<AActor*> IgnoreCharacters;
	////IgnoreCharacters.Init(Player, 1); // don't add ourselves to the resulting array

	//TArray<AActor*> CharactersNearby;

	//UKismetSystemLibrary::SphereOverlapActors(
	//	Player->GetWorld(),
	//	PlayerPos,
	//	200.0f,
	//	TraceObjectTypes,
	//	nullptr,
	//	IgnoreCharacters,
	//	CharactersNearby
	//);

	//for (AActor* overlappedActor : CharactersNearby)
	//{
	//	UE_LOG(LogTemp, Log, TEXT("OverlappedActor: %s"), *overlappedActor->GetName());


	//	//if it hits the PLAYER
	//	if (Player != nullptr)
	//	{
	//		Player->HP -= 0.1f;

	//		Explode();
	//		Destroy();
	//	}
	//}
}


// SPHERE OVERLAY
void ABomb::OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	AEnemy* EnemyAI = Cast<AEnemy>(OtherActor);

	if (EnemyAI != nullptr)
	{
		EnemyAI->Enemy_HP -= 0.3f;

		//### When hit an enemy reward the player with Ultimate Ability Points
		EnemyAI->UltimateAbilityReward();

		Explode();
		Destroy();
	}
	
}

// incase the AOE doesn't hit an enemy, it will destroy itself after 5 seconds
void ABomb::NoBomb()
{
	Explode();
	Destroy();
}







