// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneCharacter.h"

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
}

// Called when the game starts or when spawned
void ADroneCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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