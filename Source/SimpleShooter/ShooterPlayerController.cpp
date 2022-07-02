// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"

#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();
	DisplayScreenUI(HUDClass);
}

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	if(bIsWinner)
	{
		//Display Win Screen
		DisplayScreenUI(WinScreenClass);
	}
	else
	{
		//Display Lose Screen
		DisplayScreenUI(LoseScreenClass);
	}
	GetWorldTimerManager().SetTimer(RestartTimer,this,&APlayerController::RestartLevel,RestartDelay);
}
void AShooterPlayerController::DisplayScreenUI(TSubclassOf<UUserWidget> ScreenClass)
{
	UUserWidget* Screen = CreateWidget(this,ScreenClass);
	if(Screen != nullptr)
	{
		Screen->AddToViewport();
	}
}
