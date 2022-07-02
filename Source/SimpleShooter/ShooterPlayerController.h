// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
class UUserWidget;
UCLASS()
class SIMPLESHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void GameHasEnded(AActor* EndGameFocus, bool bIsWinner) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HUDClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> LoseScreenClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> WinScreenClass;

	UPROPERTY()
	UUserWidget* HUD;
	
	UPROPERTY(EditAnywhere)
	float RestartDelay = 5.f;

	FTimerHandle RestartTimer;

	void DisplayScreenUI(TSubclassOf<UUserWidget> ScreenClass, bool ShowUI);
};
