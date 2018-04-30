// Fill out your copyright notice in the Description page of Project Settings.

#include "RGQueue.h"
#include "BehaviorTree/RGBehaviorTreeBase.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"


URGQueue::URGQueue()
{
}
URGQueue::URGQueue(URGBehaviorTreeComponent*ownerComp,  TArray<URGBehaviorTreeBase*>children,int cost)
	:URGBehaviorTreeBase(ownerComp, children, cost)
{}


URGQueue::~URGQueue()
{
}
void URGQueue::Reset()
{
	URGBehaviorTreeBase::Reset();
}
EBehaviorState URGQueue::Tick_Implementation(float deltaTime)
{
	int lowest = 1000;
	bool succeed = true;
	for (int i=0; i< m_behaviorList.Num(); i++)
	{
		if (m_behaviorList[i]->behaviorState == EBehaviorState::EB_Succeed)
		{
			behaviorState = EBehaviorState::EB_Succeed;
			return behaviorState;
		}
		if (m_behaviorList[i]->m_cost <= m_lowestCost && m_behaviorList[i]->behaviorState != EBehaviorState::EB_Failed)
		{
			m_ownerComp->SetCurrentBehavior(m_behaviorList[i]);
			m_lowestCost = m_behaviorList[i]->m_cost;

		}
		if (m_behaviorList[i]->m_cost < lowest&&m_behaviorList[i]->behaviorState != EBehaviorState::EB_Failed)
		{
			lowest = m_behaviorList[i]->m_cost;

		}
		if (m_behaviorList[i]->behaviorState != EBehaviorState::EB_Failed)
			succeed = false;
	}

	m_lowestCost = lowest;
	if (succeed)
	{
		behaviorState = EBehaviorState::EB_Failed;
		return behaviorState;
	}
	behaviorState = EBehaviorState::EB_Progress;
	return behaviorState;
}