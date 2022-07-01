// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"

#include "Blueprint/UserWidget.h"

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	if(bIsWinner)
	{
		//Display Win Screen
		DisplayEndGameScreen(WinScreenClass);
	}
	else
	{
		//Display Lose Screen
		DisplayEndGameScreen(LoseScreenClass);
	}
	GetWorldTimerManager().SetTimer(RestartTimer,this,&APlayerController::RestartLevel,RestartDelay);
}

void AShooterPlayerController::DisplayEndGameScreen(TSubclassOf<UUserWidget> ScreenClass)
{
	UUserWidget* Screen = CreateWidget(this,ScreenClass);
	if(Screen != nullptr)
	{
		Screen->AddToViewport();
	}
}
