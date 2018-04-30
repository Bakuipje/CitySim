// Fill out your copyright notice in the Description page of Project Settings.

#include "RGRepeat.h"
#include "BehaviorTree/RGBehaviorTreeBase.h"
#include "BehaviorTree/RGCondition.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"

URGRepeat::URGRepeat()
{
}

URGRepeat::URGRepeat(URGBehaviorTreeComponent* ownerComp,  TArray<URGBehaviorTreeBase*> children, int cost,TArray<URGCondition*> conditions)
	:URGBehaviorTreeBase(ownerComp, children, cost), m_conditions(conditions)
{}

URGRepeat::~URGRepeat()
{
}

EBehaviorState URGRepeat::Tick_Implementation(float deltaTime)
{
	bool succes = true;
	for (int i=0; i<m_conditions.Num();i++)
	{
		if (!m_conditions[i]->Execute())
			succes = false;
	}
	if (succes)
	{
		behaviorState = EBehaviorState::EB_Succeed;
		return behaviorState;
	}
	for (int i = 0; i < m_conditions.Num(); i++)
	{
		m_behaviorList[i]->Reset();
		m_ownerComp->SetCurrentBehavior(m_behaviorList[i]);
	}
	behaviorState = EBehaviorState::EB_Progress;
	return behaviorState;
}