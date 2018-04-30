// Fill out your copyright notice in the Description page of Project Settings.

#include "FindHome.h"
#include "Building/House.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"
#include "Agent.h"
#include <AI/Navigation/NavigationPath.h>
#include <AI/Navigation/NavigationSystem.h>
#include "EngineUtils.h"


EBehaviorState UFindHome::Tick_Implementation(float deltaTime)
{
	float closestdist = 1e34;
	AHouse* bestHomePlace = nullptr;
	UWorld* world = m_ownerComp->GetOwner()->GetWorld();
	AAgent* ownerActor = (AAgent*)m_ownerComp->GetOwner();
	UNavigationSystem* NavSys = UNavigationSystem::GetCurrent(world);
	int highestCost = 0;
	if (world == nullptr)
	{
		behaviorState = EBehaviorState::EB_Failed;
		return behaviorState;
	}
	for (TActorIterator<AHouse> homeItr(world); homeItr; ++homeItr)
	{
		AHouse* HomePlace = *homeItr;
		if (!HomePlace->HasPlace(ownerActor))
			continue;
		UNavigationPath *tpath;
		tpath = NavSys->FindPathToLocationSynchronously(world, HomePlace->GetActorLocation(), m_ownerComp->GetOwner()->GetActorLocation());

		float dist = tpath->GetPathLength();
		if (HomePlace->livingCost>=highestCost&& closestdist>dist)
		{
			bestHomePlace = HomePlace;
			closestdist = dist;
			highestCost = HomePlace->livingCost;
		}
	}

	if (bestHomePlace == nullptr)
	{
		AddPrintString(FString("failed to find a home"));
		behaviorState = EBehaviorState::EB_Failed;
		return behaviorState;
	}
	AddPrintString("found a home, cost is "+ FString::FromInt(highestCost));
	ownerActor->homePlace = bestHomePlace;
	bestHomePlace->AddVisitor(ownerActor);
	ownerActor->moveLocation.Insert(bestHomePlace,0);// = bestHomePlace;
	behaviorState = EBehaviorState::EB_Succeed;
	return behaviorState;
}

