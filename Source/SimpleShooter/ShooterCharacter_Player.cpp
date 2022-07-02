// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter_Player.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AShooterCharacter_Player::AShooterCharacter_Player()
{
	PrimaryActorTick.bCanEverTick = true;
	PlayerCamSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
    PlayerCamSpringArmComponent->SetupAttachment(RootComponent);
    PlayerCam = CreateDefaultSubobject<UCameraComponent>("Player Cam");
    PlayerCam->SetupAttachment(PlayerCamSpringArmComponent);
}

// Called to bind functionality to input
void AShooterCharacter_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this,&AShooterCharacter_Player::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"),this, &AShooterCharacter_Player::LookUp);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"),this, &AShooterCharacter_Player::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"),this,&AShooterCharacter_Player::LookRight);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"),this,&AShooterCharacter_Player::LookUpRate);
	PlayerInputComponent->BindAction(TEXT("Jump"),EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"),EInputEvent::IE_Pressed,this, &AShooterCharacter::Shoot);
}
void AShooterCharacter_Player::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector()* AxisValue);
}

void AShooterCharacter_Player::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void AShooterCharacter_Player::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}


void AShooterCharacter_Player::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector()* AxisValue);
}

void AShooterCharacter_Player::LookRight(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void AShooterCharacter_Player::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

