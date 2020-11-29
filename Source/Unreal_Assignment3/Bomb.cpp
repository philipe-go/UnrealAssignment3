// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomb.h"
#include "Unreal_Assignment3Character.h"
#include "Unreal_Assignment3PlayerController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"

// Sets default values
ABomb::ABomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// if we make a Mesh in .h , we have to make a component in .cpp
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();


	
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}


void ABomb::NotifyActorBeginOverlap(AActor* OtherActor)
{
	
	//ADD "#include "Unreal_Assignment3Character.h"" on top
	AUnreal_Assignment3Character* Player = Cast<AUnreal_Assignment3Character>(OtherActor);

	FVector PlayerPos = Player->GetActorLocation();

	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;
	TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	TArray<AActor*> IgnoreCharacters;
	//IgnoreCharacters.Init(Player, 1); // don't add ourselves to the resulting array

	TArray<AActor*> CharactersNearby;

	UKismetSystemLibrary::SphereOverlapActors(
		Player->GetWorld(),
		PlayerPos,
		200.0f,
		TraceObjectTypes,
		nullptr,
		IgnoreCharacters,
		CharactersNearby
	);

	for (AActor* overlappedActor : CharactersNearby)
	{
		UE_LOG(LogTemp, Log, TEXT("OverlappedActor: %s"), *overlappedActor->GetName());


		//if it hits the PLAYER
		if (Player != nullptr)
		{
			Player->HP -= 0.1f;

			Explode();
			Destroy();
		}
	}
	

}

void ABomb::withinRadius()
{


}



