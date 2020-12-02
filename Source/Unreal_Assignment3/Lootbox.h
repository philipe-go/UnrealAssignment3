// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lootbox.generated.h"

UCLASS()
class UNREAL_ASSIGNMENT3_API ALootbox : public AActor
{

#pragma region Default Fields
	GENERATED_BODY()

public:
	ALootbox();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

#pragma endregion

#pragma region Custom Fields
public:
	// Has a visual component
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Mesh;

	///** Random generated Num **/
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int RandomNum;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//### Item type to be spawned in the trap area. Enemy should be added in the Editor
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> HealthPotion;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> ManaPotion;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> SpeedPotion;

	UFUNCTION(BlueprintImplementableEvent)
		void OnLootOpen(FVector loc, FRotator rot);

	void OpenLoot();

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* TriggerArea;
#pragma endregion
};
