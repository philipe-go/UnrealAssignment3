// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lootbox.generated.h"

UCLASS()
class UNREAL_ASSIGNMENT3_API ALootbox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALootbox();


	// Has a visual component
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Mesh;

	///** Random generated Num **/
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int RandomNum;




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OpenLoot();
};
