// Fill out your copyright notice in the Description page of Project Settings.

#include "FindLiesurePlace.h"
#include "Building/LiesureBase.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"
#include "Agent.h"
#include <AI/Navigation/NavigationPath.h>
#include <AI/Navigation/NavigationSystem.h>
#include "EngineUtils.h"


EBehaviorState UFindLiesurePlace::Tick_Implementation(float deltaTime)
{
	float closestdist = 1e34;
	ALiesureBase* bestHomePlace = nullptr;
	UWorld* world = m_ownerComp->GetOwner()->GetWorld();
	AAgent* ownerActor = (AAgent*)m_ownerComp->GetOwner();
	int highestCost = 0;
	UNavigationSystem* NavSys = UNavigationSystem::GetCurrent(world);

	if (world == nullptr)
	{
		behaviorState = EBehaviorState::EB_Failed;
		return behaviorState;
	}
	for (TActorIterator<ALiesureBase> homeItr(world); homeItr; ++homeItr)
	{
		ALiesureBase* HomePlace = *homeItr;
		if (!HomePlace->HasPlace(ownerActor))//ownerActor->budget))
			continue;
		UNavigationPath *tpath;
		tpath = NavSys->FindPathToLocationSynchronously(world, HomePlace->GetActorLocation(), m_ownerComp->GetOwner()->GetActorLocation());

		float dist = tpath->GetPathLength();
		if (HomePlace->liesureAmount > highestCost)
		{
			bestHomePlace = HomePlace;
			closestdist = dist;
			highestCost = HomePlace->liesureAmount;
		}
		if (HomePlace->liesureAmount >= highestCost&& dist < closestdist)
		{
			bestHomePlace = HomePlace;
			closestdist = dist;
			highestCost = HomePlace->liesureAmount;
		}
	}

	if (bestHomePlace == nullptr)
	{
		AddPrintString(FString("failed to find a leisureplace "));
		behaviorState = EBehaviorState::EB_Failed;
		return behaviorState;
	}
	AddPrintString("found a liesureplace, cost is " + FString::FromInt(highestCost)+" relax amount "+ FString::FromInt(bestHomePlace->liesureAmount)) ;
	ownerActor->liesurePlace = bestHomePlace;
	bestHomePlace->AddVisitor(ownerActor);
	ownerActor->moveLocation.Insert(bestHomePlace,0);// = bestHomePlace;
	behaviorState = EBehaviorState::EB_Succeed;
	return behaviorState;
}

