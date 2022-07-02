// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"

#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();
	HUD = CreateWidget(this,HUDClass);
	if(HUD != nullptr)
	{
		HUD->AddToViewport();
	}	
}

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	//Removes Player HUD from view
	HUD->RemoveFromViewport();

	if(bIsWinner)
	{
		//Display Win Screen
		DisplayScreenUI(WinScreenClass,true);
	}
	else
	{
		//Display Lose Screen
		DisplayScreenUI(LoseScreenClass,true);
	}
	GetWorldTimerManager().SetTimer(RestartTimer,this,&APlayerController::RestartLevel,RestartDelay);
}
void AShooterPlayerController::DisplayScreenUI(TSubclassOf<UUserWidget> ScreenClass, bool ShowUI)
{
	UUserWidget* Screen = CreateWidget(this,ScreenClass);
	if(Screen != nullptr && ShowUI == true)
	{
		Screen->AddToViewport();
	}
	else if(Screen != nullptr && ShowUI == false)
	{
		Screen->RemoveFromViewport();
	}
}
