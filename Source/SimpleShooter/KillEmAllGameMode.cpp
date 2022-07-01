// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"

#include "EngineUtils.h"
#include "ShooterAIController.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	PlayerController = GetPlayerControllerViaCast(PawnKilled);
	if(PlayerController != nullptr)
	{
		EndGame(false);
	}
	//for loop over Shoot AI in World
	for(AShooterAIController* AI : TActorRange<AShooterAIController>(GetWorld()))
	{
		if(!AI->IsDead())
		{
			return;
		}		
	}
	EndGame(true);
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner) const
{
	for( AController* Controller : TActorRange<AController>(GetWorld()))
	{
		const bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(),bIsWinner);
	}
}

/*APlayerController* AKillEmAllGameMode::GetPlayerControllerViaCast(APawn* Pawn)
{
	return Super::GetPlayerControllerViaCast(Pawn);
}*/
