// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveToBehavior.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"
#include "Agent.h"

UMoveToBehavior::UMoveToBehavior()
{
}
UMoveToBehavior::UMoveToBehavior(URGBehaviorTreeComponent* ownercomp,  TArray<URGBehaviorTreeBase*> children,int cost,FVector m_destination, float range)
	:URGBehaviorTreeBase(ownercomp,children, cost),m_destination(m_destination), m_range(range)
{

}


UMoveToBehavior::~UMoveToBehavior()
{
}

EBehaviorState UMoveToBehavior::Tick_Implementation(float deltaTime)
{
	
	if (m_ownerComp == NULL||!IsValid(m_ownerComp))
		return EBehaviorState::EB_Progress;
	AAgent* agent = (AAgent*)m_ownerComp->GetOwner();
	if (agent->IsNear(m_destination, agent->GetActorLocation(), m_range))
	{
		behaviorState = EBehaviorState::EB_Succeed;
		return behaviorState;
	}
	agent->MoveTo(m_destination);
	behaviorState = EBehaviorState::EB_Progress;
	return behaviorState;
}