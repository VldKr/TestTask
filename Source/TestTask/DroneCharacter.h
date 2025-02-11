// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.h"
#include "DroneCharacter.generated.h"

UCLASS()
class TESTTASK_API ADroneCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADroneCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void Death();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void MoveForward(float Value);

	UFUNCTION()
	void MoveUp(float Value);

	UFUNCTION()
	void MoveRight(float Value);

	UFUNCTION()
	void Fire();

private:

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SpawnPointProjectile;

protected:
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* GunSkeletalMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector MuzzleOffset;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UHUDWidget> HUDClass;

	UPROPERTY(BlueprintReadOnly)
	UHUDWidget* HUD;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 BulletsCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxBulletsCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxHealth;*/

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Health = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Bullets = 20.0f;

	UFUNCTION(BlueprintImplementableEvent)
	FVector GetMuzzleLocation();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
	float DamageValue = 5.0f;

public:
	void DealDamage(float DamageAmount);

	void DealBullet(float PatronAmount);

	void DealHeal(float HealAmount);

};
