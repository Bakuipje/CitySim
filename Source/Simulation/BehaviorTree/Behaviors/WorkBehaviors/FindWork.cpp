// Fill out your copyright notice in the Description page of Project Settings.

#include "FindWork.h"
#include "Building/OfficePlace.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"
#include "Agent.h"
#include <AI/Navigation/NavigationPath.h>
#include <AI/Navigation/NavigationSystem.h>
#include "EngineUtils.h"


EBehaviorState UFindWork::Tick_Implementation(float deltaTime)
{
	float closestdist = 1e34;
	AOfficePlace* bestOfficePlace = nullptr;
	UWorld* world = m_ownerComp->GetOwner()->GetWorld();
	AAgent* ownerActor = (AAgent*)m_ownerComp->GetOwner();
	UNavigationSystem* NavSys = UNavigationSystem::GetCurrent(world);

	int highestCompensation = 0;
	if (world == nullptr)
	{
		behaviorState = EBehaviorState::EB_Failed;
		return behaviorState;
	}
	for (TActorIterator<AOfficePlace> officeItr(world); officeItr; ++officeItr)
	{
		AOfficePlace* officePlace = *officeItr;
		if (!officePlace->HasJob(ownerActor))
			continue;
		UNavigationPath *tpath;
		tpath = NavSys->FindPathToLocationSynchronously(world, officePlace->GetActorLocation(), m_ownerComp->GetOwner()->GetActorLocation());

		float dist = tpath->GetPathLength();
		if (officePlace->compensation> highestCompensation)//dist < closestdist)
		{
			highestCompensation = officePlace->compensation;
			bestOfficePlace = officePlace;
			closestdist = dist;
		}
		if (officePlace->compensation >= highestCompensation&& dist<closestdist)//dist < closestdist)
		{
			highestCompensation = officePlace->compensation;
			bestOfficePlace = officePlace;
			closestdist = dist;
		}
	}

	if (bestOfficePlace == nullptr)
	{
		AddPrintString(FString("failed to find a work"));
		behaviorState = EBehaviorState::EB_Failed;
		return behaviorState;
	}
	AddPrintString("found a work"+FString::FromInt(highestCompensation));
	ownerActor->workPlace = bestOfficePlace;
	bestOfficePlace->AddVisitor(ownerActor);
	ownerActor->moveLocation.Insert(bestOfficePlace,0);
	behaviorState = EBehaviorState::EB_Succeed;
	return behaviorState;
}

