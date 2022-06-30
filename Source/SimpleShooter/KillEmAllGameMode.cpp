// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	PlayerController = GetPlayerControllerViaCast(PawnKilled);
	if(PlayerController != nullptr)
	{
		PlayerController->GameHasEnded(nullptr,false);
	}
}

/*APlayerController* AKillEmAllGameMode::GetPlayerControllerViaCast(APawn* Pawn)
{
	return Super::GetPlayerControllerViaCast(Pawn);
}*/
