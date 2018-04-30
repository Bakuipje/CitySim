// Fill out your copyright notice in the Description page of Project Settings.

#include "MovementBehavior.h"
#include "Agent.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"

#include "BehaviorTree/Behaviors/RGSequence.h"
#include "BehaviorTree/Behaviors/MoveToInteractable.h"
#include "BehaviorTree/Behaviors/Transportation/FindStation.h"
#include "BehaviorTree/Behaviors/Transportation/StationBehahavior.h"

UMovementBehavior::UMovementBehavior()
{

}

URGBehaviorTreeBase* UMovementBehavior::GetBehaviorTreeSegment(URGBehaviorTreeComponent* ownerComp)
{
	AAgent* owner = (AAgent*)ownerComp->GetOwner();

	URGSequence* trainSequence = NewObject<URGSequence>();
	UFindStation* findStation = NewObject< UFindStation>();
	findStation->m_destination = (AActor*&)destinationActor;
	UMoveToInteractable* moveToStation = NewObject<UMoveToInteractable>();
	moveToStation->m_destinationObject = (AActor*&)owner->stationPlace;
	UStationBehahavior* stationBehavior = NewObject<UStationBehahavior>();
	UMoveToInteractable* movefromStation = NewObject<UMoveToInteractable>();
	movefromStation->m_destinationObject = (AActor*&)destinationActor;

	trainSequence->m_behaviorList.Add(findStation);
	trainSequence->m_behaviorList.Add(moveToStation);
	trainSequence->m_behaviorList.Add(stationBehavior);
	trainSequence->m_behaviorList.Add(movefromStation);

	UMoveToInteractable* movetoPlace = NewObject<UMoveToInteractable>();
	movetoPlace->m_destinationObject = (AActor*&)destinationActor;
	m_behaviorList.Add(trainSequence);
	m_behaviorList.Add(movetoPlace);

	return this;
}
