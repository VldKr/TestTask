// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPawn.h"
#include "AIProjectile.h"
#include "Components/SceneComponent.h"

// Sets default values
AAIPawn::AAIPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	TurretPlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretPlatformMesh"));
	TurretPlatformMesh->SetupAttachment(SceneComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(TurretPlatformMesh);

	SpawnPointProjectile = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPointProjectile"));
	SpawnPointProjectile->SetupAttachment(TurretMesh);
}

void AAIPawn::ParamProjectile()
{
	GetWorld()->SpawnActor<AAIProjectile>(TurretProjectile, SpawnPointProjectile->GetComponentLocation(), SpawnPointProjectile->GetComponentRotation());
}

// Called when the game starts or when spawned
void AAIPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FVector AAIPawn::GetPointLocation() const
{
	if (SpawnPointProjectile)
	{
		return SpawnPointProjectile->GetComponentLocation();
	}
	return FVector();
}