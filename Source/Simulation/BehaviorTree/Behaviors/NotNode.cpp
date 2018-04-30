// Fill out your copyright notice in the Description page of Project Settings.

#include "NotNode.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"

UNotNode::UNotNode()
{
}

UNotNode::~UNotNode()
{
}

EBehaviorState UNotNode::Tick(float deltaTime)
{
	for (int i = 0; i < m_behaviorList.Num(); i++)
	{
		if (m_behaviorList[i]->behaviorState == EBehaviorState::EB_Succeed)
		{
			behaviorState = EBehaviorState::EB_Failed;
			return behaviorState;
		}
		if (m_behaviorList[i]->behaviorState == EBehaviorState::EB_Failed)
		{
			behaviorState = EBehaviorState::EB_Succeed;
			return behaviorState;
		}
	}
	behaviorState = EBehaviorState::EB_Failed;
	return behaviorState;
}
