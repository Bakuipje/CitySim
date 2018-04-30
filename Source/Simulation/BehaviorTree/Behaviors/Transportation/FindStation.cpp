// Fill out your copyright notice in the Description page of Project Settings.

#include "FindStation.h"
#include "Building/Station.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"
#include "Agent.h"
#include "EngineUtils.h"
#include <AI/Navigation/NavigationPath.h>
#include <AI/Navigation/NavigationSystem.h>

EBehaviorState UFindStation::Tick_Implementation(float delaTime)
{
	float closestDist = 1e34;
	AStation* closestStation = nullptr;
	UWorld* world = m_ownerComp->GetOwner()->GetWorld();
	AAgent* ownerActor = (AAgent*)m_ownerComp->GetOwner();
	AStation* destinationStation = GetDestinationStation(ownerActor->moveLocation[0], ownerActor);

	if (destinationStation == nullptr)
	{
		AddPrintString(FString("failed to find a destination station"));
		behaviorState = EBehaviorState::EB_Failed;
		return behaviorState;
	}

	for (TActorIterator<AStation> stationItr(world); stationItr; ++stationItr)
	{
		AStation* stationPlace = *stationItr;
		if (!stationPlace->HasPLace(ownerActor))
			continue;
		float dist = FVector::DistSquared2D(stationPlace->GetActorLocation(), ownerActor->GetActorLocation());
		if (dist < closestDist&& destinationStation->HasStation(TArray<AStation*>(), stationPlace)&& stationPlace!= destinationStation)
		{
			closestDist = dist;
			closestStation = stationPlace;
		}

	}

	if (closestStation == nullptr||closestStation == destinationStation)
	{
		AddPrintString(FString("failed to find a station"));
		behaviorState = EBehaviorState::EB_Failed;
		return behaviorState;
	}
	AddPrintString(FString("found a station, cost is " + FString::FromInt(closestStation->cost)));
	ownerActor->stationPlace = closestStation;
	ownerActor->moveLocation.Insert(closestStation, 0);
	behaviorState = EBehaviorState::EB_Succeed;

	return behaviorState;
}

AStation* UFindStation::GetDestinationStation(AActor* destination, AActor* owner)
{
	AStation* closestStation = nullptr;
	UWorld* world = m_ownerComp->GetOwner()->GetWorld();
	float closestDist = 1e34;
	UNavigationSystem* NavSys = UNavigationSystem::GetCurrent(world);
	for (TActorIterator<AStation> stationItr(world); stationItr; ++stationItr)
	{
		AStation* stationPlace = *stationItr;

		float dist = FVector::DistSquared2D(stationPlace->GetActorLocation(), destination->GetActorLocation());
		if (dist < closestDist)
		{
			closestDist= dist;
			closestStation = stationPlace;
		}

	}
	if (closestStation != nullptr)
	{
		UNavigationPath *tpath;
		tpath = NavSys->FindPathToLocationSynchronously(world, destination->GetActorLocation(), owner->GetActorLocation());
		float distDest = tpath->GetPathLength();// FVector::Dist2D(destination->GetActorLocation(), owner->GetActorLocation());
		tpath = NavSys->FindPathToLocationSynchronously(world, closestStation->GetActorLocation(), owner->GetActorLocation());

		float distStation = tpath->GetPathLength(); //FVector::Dist2D(closestStation->GetActorLocation(), owner->GetActorLocation());
		if (distStation > distDest)
			closestStation = nullptr;
	}
	return closestStation;

}