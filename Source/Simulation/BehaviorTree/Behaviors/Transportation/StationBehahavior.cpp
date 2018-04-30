// Fill out your copyright notice in the Description page of Project Settings.

#include "StationBehahavior.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"
#include "Building/Station.h"
#include "Transportation/Train.h"
#include "Agent.h"
#include "EngineUtils.h"
#include <AI/Navigation/NavigationPath.h>
#include <AI/Navigation/NavigationSystem.h>

EBehaviorState UStationBehahavior::Tick_Implementation(float deltaTime)
{
	AAgent* ownerActor = (AAgent*)m_ownerComp->GetOwner();
	AStation* currentStation = ownerActor->stationPlace;
	if (destinationStation == nullptr)
	{
		destinationStation = GetDestinationStation(ownerActor->moveLocation[0]);
	}
	if (destinationStation == currentStation)
	{
		ownerActor->moveLocation.Empty();
		behaviorState = EBehaviorState::EB_Failed;
		return behaviorState;
	}
	if (currentStation->currentTrain != nullptr)
	{
		train = currentStation->currentTrain;
		behaviorState = EBehaviorState::EB_Progress;
		return behaviorState;
	}
	if (train != nullptr &&train == destinationStation->currentTrain)
	{
		ownerActor->SetActorLocation(destinationStation->GetDestination(ownerActor)+FVector(FMath::RandRange(-100,100), FMath::RandRange(-100, 100),100));
		train = nullptr;
		behaviorState = EBehaviorState::EB_Succeed;
		return behaviorState;
	}
	if (train != nullptr)
	{
		ownerActor->SetActorLocation(train->GetActorLocation());
	}
	behaviorState = EBehaviorState::EB_Progress;
	return behaviorState;
}

AStation* UStationBehahavior::GetDestinationStation(AActor* m_destination)
{
	AStation* closestStation = nullptr;
	UWorld* world = m_ownerComp->GetOwner()->GetWorld();
	float closestDist = 1e34;
	UNavigationSystem* NavSys = UNavigationSystem::GetCurrent(world);

	for (TActorIterator<AStation> stationItr(world); stationItr; ++stationItr)
	{
		AStation* stationPlace = *stationItr;
		UNavigationPath *tpath;
		tpath = NavSys->FindPathToLocationSynchronously(world, stationPlace->GetActorLocation(), m_destination->GetActorLocation());

		float dist = tpath->GetPathLength();// FVector::DistSquared2D(stationPlace->GetActorLocation(), m_destination->GetActorLocation());
		if (dist < closestDist)
		{
			closestDist = dist;
			closestStation = stationPlace;
		}

	}
	return closestStation;

}