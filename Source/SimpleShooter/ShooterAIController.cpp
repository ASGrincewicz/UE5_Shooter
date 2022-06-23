// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	if(AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"),GetPawn()->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"),PlayerPawn->GetActorLocation());
	}	
}

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	
	/*if(LineOfSightTo(PlayerPawn))
	{
		SetFocus(PlayerPawn,EAIFocusPriority::Gameplay);
		MoveToActor(PlayerPawn,300.f);
	}
	else
	{
		ClearFocus(EAIFocusPriority::Gameplay);
		StopMovement();
	}*/
	
		
}
