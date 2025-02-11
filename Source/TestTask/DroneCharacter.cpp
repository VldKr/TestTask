// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneCharacter.h"
#include "Projectile.h"

// Sets default values
ADroneCharacter::ADroneCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(CameraComponent != nullptr)
	CameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
	CameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, BaseEyeHeight));
	CameraComponent->bUsePawnControlRotation = true;

	GunSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunSkeletalMeshComponent"));
	GunSkeletalMeshComponent->bCastDynamicShadow = false;
	GunSkeletalMeshComponent->CastShadow = false;
	GunSkeletalMeshComponent->SetupAttachment(CameraComponent);

	//SpawnPointProjectile = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPointProjectile"));
	//SpawnPointProjectile->SetupAttachment(GunSkeletalMeshComponent);

	/*MaxBulletsCount = 12;
	BulletsCount = MaxBulletsCount;

	MaxHealth = 100;
	Health = MaxHealth;*/
}

// Called when the game starts or when spawned
void ADroneCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GetCharacterMovement()->SetMovementMode(MOVE_Flying);
}

// Called every frame
void ADroneCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADroneCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADroneCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADroneCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MoveUp", this, &ADroneCharacter::MoveUp);
	PlayerInputComponent->BindAxis("Turn", this, &ADroneCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ADroneCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ADroneCharacter::Fire);
}

void ADroneCharacter::MoveForward(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(GetCapsuleComponent()->GetForwardVector(), Value);
}

void ADroneCharacter::MoveRight(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void ADroneCharacter::MoveUp(float Value)
{
	FVector Dir = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Z);
	AddMovementInput(Dir, Value);
}

void ADroneCharacter::Fire()
{
	if (ProjectileClass)
	{
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		//FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
		FVector MuzzleLocation = GetMuzzleLocation();
		FRotator MuzzleRotation = CameraRotation;

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
		if (Projectile)
		{
			FVector LaunchDirection = MuzzleRotation.Vector();
			Projectile->FireInDirection(LaunchDirection);
		}
		Bullets -= 1.0f;
		if (Bullets == 0.0f)
		{
			Bullets = 20.0f;
		}
	}
}

void ADroneCharacter::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	/*AEnemyU* Char = Cast<AEnemyU>(OtherActor);

	if (Char)
	{
		Char->DealDamage(DamageValue);
	}*/
}

void ADroneCharacter::DealDamage(float DamageAmount)
{
	Health -= DamageAmount;

	if (Health <= 0.0f)
	{
		Destroy();
	}

}

void ADroneCharacter::DealHeal(float HealAmount)
{
	if (Health == 100.0f)
	{

	}
	else
	{
		Health = 100.0f;
	}
}

void ADroneCharacter::DealBullet(float PatronAmount)
{
	if (Bullets == 20.0f)
	{

	}
	else
	{
		Bullets = 20.0f;
	}
}