// Fill out your copyright notice in the Description page of Project Settings.

#include "RGParrallel.h"
#include "BehaviorTree/RGBehaviorTreeBase.h"

URGParrallel::URGParrallel()
{
}

URGParrallel::~URGParrallel()
{
}



EBehaviorState URGParrallel::Tick_Implementation(float deltaTime)
{
	bool finished = true;
	behaviorState = EBehaviorState::EB_Progress;
	for (int i=0; i<m_behaviorList.Num(); i++)
	{
		if (m_behaviorList[i]->behaviorState == EBehaviorState::EB_Failed)
		{
			behaviorState = EBehaviorState::EB_Failed;
			return behaviorState;
		}
		if ((m_behaviorList[i]->behaviorState == EBehaviorState::EB_Failed))
			finished = false;
		m_behaviorList[i]->Tick(deltaTime);
	}
	if (finished)
	{
		behaviorState = EBehaviorState::EB_Succeed;
	}
	return behaviorState;
	
}