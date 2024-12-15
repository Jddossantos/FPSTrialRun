// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/BTT_GetRandomLocation.h"

EBTNodeResult::Type UBTT_GetRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// 1. Get random point on the nav mesh
	// 2. Set the blackboard random patrol location
	// 3. Return if we succeeded or not

	NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	if (NavArea) 
	{
		AEnemyAIController* AIOwner = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());	//Casting to AI Controller
		//Getting Random Point that is reachable
		NavArea->K2_GetRandomReachablePointInRadius(GetWorld(), AIOwner->GetPawn()->GetActorLocation(), RandomLocation, 2000.0f);
	}
	else 
	{
		//Else return failed
		return EBTNodeResult::Failed;
	}

	//Getting Black Board location, setting vector at random locations
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("Random Patrol Location"), RandomLocation);

	return EBTNodeResult::Succeeded;
}
