// Copyright Epic Games, Inc. All Rights Reserved.

#include "Unreal_Assignment3Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"

AUnreal_Assignment3Character::AUnreal_Assignment3Character()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// Add Projectile
	ProjectileOrigin = CreateAbstractDefaultSubobject<USceneComponent>(TEXT("ProjectileOrigin"));
	ProjectileOrigin->SetupAttachment(RootComponent);

	// Add AOE Projectile
	AOEOrigin = CreateAbstractDefaultSubobject<USceneComponent>(TEXT("AOEOrigin"));
	AOEOrigin->SetupAttachment(RootComponent);

	//### Get the Character Movement and set initial speed
	InitialSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

void AUnreal_Assignment3Character::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (CursorToWorld != nullptr)
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UWorld* World = GetWorld())
			{

				FHitResult HitResult;
				FCollisionQueryParams Params(NAME_None, FCollisionQueryParams::GetUnknownStatId());
				FVector StartLocation = TopDownCameraComponent->GetComponentLocation();
				FVector EndLocation = TopDownCameraComponent->GetComponentRotation().Vector() * 2000.0f;
				Params.AddIgnoredActor(this);
				World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
				FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
				CursorToWorld->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);
			}
		}
		else if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}

	if (bIsFast)
	{
		ElapsedTime--;
		if (ElapsedTime < 10)
		{
			bIsFast = false;
			GetCharacterMovement()->MaxWalkSpeed = InitialSpeed;
		}
	}
}

void AUnreal_Assignment3Character::Shoot()
{
	GetWorld()->SpawnActor<AActor>(ProjectileActor, ProjectileOrigin->GetComponentTransform());
	ShootAnim();
}

void AUnreal_Assignment3Character::AOE()
{
	GetWorld()->SpawnActor<AActor>(AOEActor, AOEOrigin->GetComponentTransform());
}

void AUnreal_Assignment3Character::Dodging()
{
	HP = currHP;
}

void AUnreal_Assignment3Character::hitsPlayer()
{
	//enemyDMG = 0.1f
	HP = HP - enemyDMG;
	currHP = HP;
}

void AUnreal_Assignment3Character::UseHPPotion()
{
	if (HPPotions > 0)
	{
		HPPotions--;
		HP = HP >= 1 ? 1 : HP + .1;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(0, 2, FColor::Magenta, TEXT("No HP Potion to use"));
	}
}

void AUnreal_Assignment3Character::UseManaPotion()
{
	if (ManaPotions > 0)
	{
		ManaPotions--;
		Mana = Mana >= 1 ? 1 : Mana + .1;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(0, 2, FColor::Magenta, TEXT("No Mana Potion to use"));
	}
}

void AUnreal_Assignment3Character::UseSpeedPotion()
{
	if (SpeedPotions > 0)
	{
		SpeedPotions--;
		bIsFast = true;
		ElapsedTime = SPEED_POTION_EFFECT;
		GetCharacterMovement()->MaxWalkSpeed = InitialSpeed * 4;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(0, 2, FColor::Magenta, TEXT("No Speed Potion to use"));
	}
}
