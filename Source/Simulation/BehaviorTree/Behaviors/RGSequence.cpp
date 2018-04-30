// Fill out your copyright notice in the Description page of Project Settings.

#include "RGSequence.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"

URGSequence::URGSequence()
{
}

URGSequence::~URGSequence()
{
}
URGSequence::URGSequence(URGBehaviorTreeComponent* ownerComp,  TArray<URGBehaviorTreeBase*> children, int cost)
: URGBehaviorTreeBase(ownerComp,children, cost)
{
}

EBehaviorState URGSequence::Tick_Implementation(float deltaTime)
{
	for (int i=0; i<m_behaviorList.Num(); i++)
	{
		if (m_behaviorList[i]->behaviorState == EBehaviorState::EB_Failed)
		{
			behaviorState = EBehaviorState::EB_Failed;
			return behaviorState;
		}
		if (m_behaviorList[i]->behaviorState != EBehaviorState::EB_Succeed)
		{
			behaviorState = EBehaviorState::EB_Progress;
			m_ownerComp->SetCurrentBehavior(m_behaviorList[i]);
			return behaviorState;
		}

	}
	behaviorState = EBehaviorState::EB_Succeed;
	return behaviorState;
}