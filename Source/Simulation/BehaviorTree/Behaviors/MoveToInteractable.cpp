// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveToInteractable.h"
#include "Agent.h"
#include "interactables/InteractableBase.h"
#include "interactables/StorageBase.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"
#include "Building/BuildingBase.h"
UMoveToInteractable::UMoveToInteractable()
{
}

UMoveToInteractable::~UMoveToInteractable()
{
}

EBehaviorState UMoveToInteractable::Tick_Implementation(float deltaTime)
{
	AAgent* agent = (AAgent*)m_ownerComp->GetOwner();
	if (agent->moveLocation.Num() == 0)
	{
		behaviorState = EBehaviorState::EB_Failed;
		return behaviorState;
	}
 	if (agent->moveLocation[0]->IsA(ABuildingBase::StaticClass()))
		return MoveToStorage(deltaTime);
	return MoveToDestination(deltaTime);
}

EBehaviorState UMoveToInteractable::MoveToStorage(float deltaTime)
{
	AAgent* agent = (AAgent*)m_ownerComp->GetOwner();
	ABuildingBase* m_destination = (ABuildingBase*)agent->moveLocation[0];
	if (agent->moveLocation[0] == nullptr)
	{
		behaviorState = EBehaviorState::EB_Failed;
		return behaviorState;
	}
	if (agent->IsNear(m_destination->GetDestination(agent), agent->GetActorLocation(), m_range))
	{
		agent->moveLocation.RemoveAt(0);
		behaviorState = EBehaviorState::EB_Succeed;
		return behaviorState;
	}
	agent->stamina -= deltaTime;
	agent->MoveTo(m_destination->GetDestination(agent));
	behaviorState = EBehaviorState::EB_Progress;
	return behaviorState;
}

EBehaviorState UMoveToInteractable::MoveToDestination(float deltaTime)
{
	AAgent* agent = (AAgent*)m_ownerComp->GetOwner();
	if ((m_destinationObject) == nullptr)
	{
		behaviorState = EBehaviorState::EB_Failed;
		return behaviorState;
	}
	if (agent->IsNear((m_destinationObject)->GetActorLocation(), agent->GetActorLocation(), m_range))
	{
		behaviorState = EBehaviorState::EB_Succeed;
		return behaviorState;
	}
	agent->MoveTo((m_destinationObject)->GetActorLocation());
	behaviorState = EBehaviorState::EB_Progress;
	return behaviorState;
}