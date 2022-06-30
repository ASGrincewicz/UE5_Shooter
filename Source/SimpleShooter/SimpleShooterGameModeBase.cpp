// Copyright Epic Games, Inc. All Rights Reserved.


#include "SimpleShooterGameModeBase.h"

void ASimpleShooterGameModeBase::PawnKilled(APawn* PawnKilled)
{
}

APlayerController* ASimpleShooterGameModeBase::GetPlayerControllerViaCast(APawn* Pawn)
{
	PlayerController = Cast<APlayerController>(Pawn->GetController());

	return PlayerController;
}
