// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"

#include "Gun.h"
#include "SimpleShooterGameModeBase.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	PlayerCamSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	PlayerCamSpringArmComponent->SetupAttachment(RootComponent);
	PlayerCam = CreateDefaultSubobject<UCameraComponent>("Player Cam");
	PlayerCam->SetupAttachment(PlayerCamSpringArmComponent);
	
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	
	GetMesh()->HideBoneByName(TEXT("weapon_r"),EPhysBodyOp::PBO_None);
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	
	if(Gun)
	{
		Gun->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("WeaponSocket"));
		Gun->SetOwner(this);
	}	
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this,&AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"),this, &AShooterCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"),this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"),this,&AShooterCharacter::LookRight);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"),this,&AShooterCharacter::LookUpRate);
	PlayerInputComponent->BindAction(TEXT("Jump"),EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"),EInputEvent::IE_Pressed,this, &AShooterCharacter::Shoot);
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount,DamageEvent,EventInstigator,DamageCauser);

	//Prevent the Health from going below 0.
	DamageToApply = FMath::Min(Health,DamageToApply);

	Health -= DamageToApply;

	UE_LOG(LogTemp,Warning, TEXT("Character took %f Damage and has %f Health remaining."),DamageToApply, Health);

	if(IsDead())
	{
		ASimpleShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
		if(GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);		
	}

	return DamageToApply;
}

bool AShooterCharacter::IsDead() const
{
	return Health <= 0;
}




void AShooterCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector()* AxisValue);
}

void AShooterCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void AShooterCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}


void AShooterCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector()* AxisValue);
}

void AShooterCharacter::LookRight(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void AShooterCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::Shoot()
{
	Gun->PullTrigger();
}







