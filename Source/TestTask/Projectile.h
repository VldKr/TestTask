// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

UCLASS()
class TESTTASK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	/*UFUNCTION()
	void ProjectileRotate();*/

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void FireInDirection(const FVector& Direction);

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = Projectile)
	UStaticMeshComponent* ProjectileMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = Projectile)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, Category = Projectile)
	float LifeSpan = 3.0f;

	UPROPERTY(EditAnywhere, Category = Projectile)
	float RotationDelayTime = .2f;

	UPROPERTY(EditAnywhere, Category = Projectile)
	float ForwardSpeed = 10;

	UPROPERTY(EditAnywhere, Category = Projectile)
	float RotationSpeed = 2;

	UPROPERTY(EditAnywhere, Category = Projectile)
	float RotationDegree = 5.0f;

	UPROPERTY(EditAnywhere, Category = Projectile)
	bool bCanRotate = true;

public:

	UPROPERTY(EditAnywhere)
	float DamageValue = 33.3f;

private:
	FVector ForwardVector;

	FVector RightVector;

	FRotator VectorRotation;

	FTimerHandle RotateDelayTimerHandle;

};
