// Fill out your copyright notice in the Description page of Project Settings.

#include "FindGym.h"
#include "Building/AthleticPlace.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"
#include "Agent.h"
#include <AI/Navigation/NavigationPath.h>
#include <AI/Navigation/NavigationSystem.h>
#include "EngineUtils.h"

EBehaviorState UFindGym::Tick_Implementation(float deltaTime)
{
	float closestDist = 1e34;
	AAthleticPlace* bestAthleticPlace = nullptr;
	UWorld* world = m_ownerComp->GetOwner()->GetWorld();
	AAgent* ownerActor = (AAgent*)m_ownerComp->GetOwner();
	UNavigationSystem* NavSys = UNavigationSystem::GetCurrent(world);

	float highestExperience=0;
	if (world == nullptr)
	{
		behaviorState = EBehaviorState::EB_Failed;
		return behaviorState;
	}
	for (TActorIterator<AAthleticPlace> gymItr(world); gymItr; ++gymItr)
	{
		AAthleticPlace* gymPlace = *gymItr;
		if(!gymPlace->HasPlace(ownerActor))
			continue;

		UNavigationPath *tpath;
		tpath = NavSys->FindPathToLocationSynchronously(world, gymPlace->GetActorLocation(), m_ownerComp->GetOwner()->GetActorLocation());

		float dist = tpath->GetPathLength();
		if (gymPlace->exersiceGain > highestExperience)
		{
			bestAthleticPlace = gymPlace;
			highestExperience = gymPlace->cost;
			closestDist = dist;
		}
		if (gymPlace->exersiceGain > highestExperience&& dist < closestDist)
		{
			bestAthleticPlace = gymPlace;
			highestExperience = gymPlace->cost;
			closestDist = dist;
		}

	}
	if (bestAthleticPlace == nullptr)
	{
		AddPrintString(FString("failed to find a Gym"));
		behaviorState = EBehaviorState::EB_Failed;
		return behaviorState;
	}
	AddPrintString("found a gym, cost is " + FString::FromInt(bestAthleticPlace->cost) + "exersice gain " + FString::SanitizeFloat(bestAthleticPlace->exersiceGain));
	ownerActor->gym = bestAthleticPlace;
	bestAthleticPlace->AddVisitor(ownerActor);
	ownerActor->moveLocation.Insert(bestAthleticPlace, 0);
	behaviorState = EBehaviorState::EB_Succeed;
	return behaviorState;
}

