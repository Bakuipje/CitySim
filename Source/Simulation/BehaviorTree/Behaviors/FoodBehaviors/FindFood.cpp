// Fill out your copyright notice in the Description page of Project Settings.

#include "FindFood.h"
#include "Building/FoodPlace.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"
#include "Agent.h"
#include <AI/Navigation/NavigationPath.h>
#include <AI/Navigation/NavigationSystem.h>
#include "EngineUtils.h"


EBehaviorState UFindFood::Tick_Implementation(float deltaTime)
{
	float closestdist = 1e34;
	AFoodPlace* besfoodPlace = nullptr;
	UWorld* world = m_ownerComp->GetOwner()->GetWorld();
	AAgent* ownerActor = (AAgent*)m_ownerComp->GetOwner();
	UNavigationSystem* NavSys = UNavigationSystem::GetCurrent(world);

	int highestCost = 0;
	if (world == nullptr)
	{
		behaviorState = EBehaviorState::EB_Failed;
		return behaviorState;
	}
	for (TActorIterator<AFoodPlace> homeItr(world); homeItr; ++homeItr)
	{
		AFoodPlace* FoodPlace = *homeItr;
		if (!FoodPlace->HasPlace(ownerActor))
			continue;
		UNavigationPath *tpath;
		tpath = NavSys->FindPathToLocationSynchronously(world, FoodPlace->GetActorLocation(), m_ownerComp->GetOwner()->GetActorLocation());

		float dist = tpath->GetPathLength();
		if (FoodPlace->cost > highestCost)
		{
			besfoodPlace = FoodPlace;
			closestdist = dist;
			highestCost = FoodPlace->cost;
		}
		if (FoodPlace->cost >= highestCost && dist<closestdist)
		{
			besfoodPlace = FoodPlace;
			closestdist = dist;
			highestCost = FoodPlace->cost;
		}
	}

	if (besfoodPlace == nullptr)
	{
		AddPrintString(FString("failed to find a foodPlace"));
		behaviorState = EBehaviorState::EB_Failed;
		return behaviorState;
	}
	AddPrintString("found a foodplace, cost is " + FString::FromInt(highestCost) + "bring food " + FString::FromInt(besfoodPlace->foodAmount));
	ownerActor->foodPlace = besfoodPlace;
	besfoodPlace->AddVisitor(ownerActor);
	ownerActor->moveLocation.Insert(besfoodPlace, 0);
	behaviorState = EBehaviorState::EB_Succeed;
	return behaviorState;
}




