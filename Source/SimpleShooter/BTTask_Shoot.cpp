// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"

#include "AIController.h"
#include "ShooterCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	OwnerAI = OwnerComp.GetAIOwner();
	//Check it AI controller is null
	if(OwnerAI == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	//Cast Pawn to ShootCharacter
	Character = Cast<AShooterCharacter>(OwnerAI->GetPawn());
	//Check if Character is null
	if(Character == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	//Shoot
	Character->Shoot();
	return EBTNodeResult::Succeeded;
}
