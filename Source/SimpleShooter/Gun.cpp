// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include <concrt.h>

#include "EnvironmentQuery/EnvQueryTypes.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash,Mesh,TEXT("MuzzleFlashSocket"));
	//Use the Pawn class rather than the ShootCharacter so any Pawn could potentially own the gun.
	//If the gun is limited to Characters, use the ShootCharacter.
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(OwnerPawn == nullptr) return;
	AController* OwnerController = OwnerPawn->GetController();
	if(OwnerController == nullptr) return;
	FVector ViewPointLocation;
	FRotator ViewPointRotation;
	OwnerController->GetPlayerViewPoint(ViewPointLocation,ViewPointRotation);
	
	FVector End = ViewPointLocation + ViewPointRotation.Vector() * MaxRange;
	
	FHitResult Hit;
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit,ViewPointLocation,End,ECollisionChannel::ECC_GameTraceChannel1);
	if(bSuccess)
	{
		FVector ShotDirection = -ViewPointRotation.Vector();
		//DrawDebugPoint(GetWorld(), Hit.Location, 20, FColor::Red, true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ImpactEffect,Hit.Location,ShotDirection.Rotation());
	}


	//DrawDebugCamera(GetWorld(), ViewPointLocation, ViewPointRotaion,90,2,FColor::Red,true);
}


