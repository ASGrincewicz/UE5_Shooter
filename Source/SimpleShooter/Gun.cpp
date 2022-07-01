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

bool AGun::GunTrace(FHitResult& HitResult, FVector& ShotDirection)
{
	AController* OwnerController = GetOwnerController();
	if(OwnerController == nullptr) return false;
	FVector ViewPointLocation;
	FRotator ViewPointRotation;
	OwnerController->GetPlayerViewPoint(ViewPointLocation,ViewPointRotation);
	ShotDirection = -ViewPointRotation.Vector();	
	FVector End = ViewPointLocation + ViewPointRotation.Vector() * MaxRange;	
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(HitResult,ViewPointLocation,End,ECollisionChannel::ECC_GameTraceChannel1,Params);
}

AController* AGun::GetOwnerController() const
{
	//Use the Pawn class rather than the ShootCharacter so any Pawn could potentially own the gun.
	//If the gun is limited to Characters, use the ShootCharacter.
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(OwnerPawn == nullptr) return nullptr;
	AController* OwnerController = OwnerPawn->GetController();
	return  OwnerController;
}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash,Mesh,TEXT("MuzzleFlashSocket"));
	FHitResult Hit;
	FVector ShotDirection;
	bool bSuccess = GunTrace(Hit,ShotDirection);
	
	if(bSuccess)
	{		
		//DrawDebugPoint(GetWorld(), Hit.Location, 20, FColor::Red, true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ImpactEffect,Hit.Location,ShotDirection.Rotation());
		FPointDamageEvent DamageEvent(DamageAmount, Hit, ShotDirection, nullptr);
		AActor* HitActor = Hit.GetActor();
		if(HitActor != nullptr)
		{
			HitActor->TakeDamage(DamageAmount,DamageEvent,GetOwnerController(), this);
		}
	}
	//DrawDebugCamera(GetWorld(), ViewPointLocation, ViewPointRotaion,90,2,FColor::Red,true);
}


