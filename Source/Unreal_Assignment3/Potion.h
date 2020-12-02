// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Potion.generated.h"

UENUM()
enum class EPotionType : uint8 {
	HEALTH,
	MANA,
	SPEED,
};

UCLASS()
class UNREAL_ASSIGNMENT3_API APotion : public AActor
{

#pragma region Default Fields
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APotion();

protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

#pragma endregion

#pragma region Custom Fields
public:
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* MeshComponent;

	void NotifyActorBeginOverlap(AActor* OtherActor);

	UPROPERTY(EditAnywhere)
		EPotionType PotionType;

private:


#pragma endregion

};
