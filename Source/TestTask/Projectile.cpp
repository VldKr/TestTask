// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "DroneCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}
	if (!CollisionComponent)
	{
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		CollisionComponent->InitSphereRadius(15.0f);
		RootComponent = CollisionComponent;
	}

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(RootComponent);
	ProjectileMovementComponent->InitialSpeed = 3000.f;
	ProjectileMovementComponent->MaxSpeed = 3000.f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

	ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
	ProjectileMeshComponent->SetupAttachment(RootComponent);

	InitialLifeSpan = LifeSpan;

	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	CollisionComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	/*CollisionComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	SetLifeSpan(LifeSpan);

	ForwardVector = GetActorForwardVector();
	RightVector = GetActorRightVector();*/
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	/*if (Cast<ADroneCharacter>(GetOwner()))
	{
		ProjectileMovementComponent->Velocity = (ForwardVector * ForwardSpeed + RightVector * RotationSpeed).GetSafeNormal()
			* ProjectileMovementComponent->InitialSpeed;
		//SetActorRotation(ForwardVector.Rotation());
		//AddActorLocalRotation(VectorRotation.Add(0, 0, RotationDegree));
		RightVector = RightVector.RotateAngleAxis(-RotationDegree, ForwardVector);

		if (bCanRotate)
		{
			bCanRotate = false;
			GetWorld()->GetTimerManager().SetTimer(
				RotateDelayTimerHandle, this, &AProjectile::ProjectileRotate, RotationDelayTime, false);
		}
	}*/


}

/*void AProjectile::ProjectileRotate()
{
	bCanRotate = true;
	if (RotationDegree > 0.5f) RotationDegree -= 0.1f;
	GetWorldTimerManager().ClearTimer(RotateDelayTimerHandle);
}*/

/*void AProjectile::FireInDirection(const FVector& Direction)
{
	ProjectileMovementComponent->Velocity = Direction * ProjectileMovementComponent->InitialSpeed;
}*/

/*void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	static const float Impulse = 10.0f;

	if (OtherActor != this)
	{
		TSubclassOf<UDamageType> Damage;
		UGameplayStatics::ApplyDamage(OtherActor, 35.0f, NULL, this, Damage);

		if (OtherComponent->IsSimulatingPhysics())
		{
			OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * Impulse, Hit.ImpactPoint);
		}

		Destroy();
	}
}*/

void AProjectile::FireInDirection(const FVector& Direction)
{
	ProjectileMovementComponent->Velocity = Direction * ProjectileMovementComponent->InitialSpeed;
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	static const float Impulse = 10.0f;

	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())//&& !OtherActor->GetClass()->IsChildOf(AFPSCharacter::StaticClass())
	{

		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * Impulse, Hit.ImpactPoint);

	}
	/*AEnemy* Enemy = Cast<AEnemy>(OtherActor);
	if (Enemy)
	{
		Enemy->DealDamage(DamageValue);
	}
	AFPSCharacter* Character = Cast<AFPSCharacter>(OtherActor);
	if (Character)
	{
		Character->DealDamage(DamageValue);
	}
	AEnemyU* EnemyU = Cast<AEnemyU>(OtherActor);
	if (EnemyU)
	{
		EnemyU->DealDamage(DamageValue);
	}
	Destroy();*/
}