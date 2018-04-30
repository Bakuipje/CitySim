// Fill out your copyright notice in the Description page of Project Settings.

#include "RGTimer.h"
#include "BehaviorTree/RGBehaviorTreeBase.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"

URGTimer::URGTimer()
{
}
/*
URGTimer::URGTimer(URGBehaviorTreeComponent* ownerComp, TArray<URGBehaviorTreeBase*> children, int cost, float time)
	:URGBehaviorTreeBase(ownerComp, children, cost), m_time(time), m_timer(time)
{}
*/
URGTimer::~URGTimer()
{
}
void URGTimer::BeginPlay()
{
	URGBehaviorTreeBase::BeginPlay();
	m_timer = m_time;
}

void URGTimer::Reset()
{
	URGBehaviorTreeBase::Reset();
	m_timer = m_time;
}

EBehaviorState URGTimer::Tick_Implementation(float deltaTime)
{
	if (m_timer <= 0)
	{
		behaviorState = EBehaviorState::EB_Succeed;
		return behaviorState;
	}
	m_timer -= deltaTime;
	behaviorState = EBehaviorState::EB_Progress;
	return behaviorState;
}