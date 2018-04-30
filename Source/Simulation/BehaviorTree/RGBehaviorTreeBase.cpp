// Fill out your copyright notice in the Description page of Project Settings.

#include "RGBehaviorTreeBase.h"
#include "RGBehaviorTreeComponent.h"
#include "MoodComponent.h"
#include "Agent.h"

URGBehaviorTreeBase::URGBehaviorTreeBase()
{
	m_parent = nullptr;
	m_cost = 0;
}
URGBehaviorTreeBase::URGBehaviorTreeBase(FObjectInitializer const& ObjectInitializer)
{ }
URGBehaviorTreeBase::URGBehaviorTreeBase(URGBehaviorTreeComponent* ownercomp, TArray<URGBehaviorTreeBase*> children, int cost)
{
	m_parent = nullptr;
	m_behaviorList = children;
	m_ownerComp = ownercomp;
	m_cost = cost;

}

void URGBehaviorTreeBase::BeginPlay()
{
	for (int i = 0; i < m_behaviorList.Num(); i++)
	{
		m_behaviorList[i]->m_ownerComp = m_ownerComp;
		m_behaviorList[i]->m_parent = this;
		m_behaviorList[i]->BeginPlay();
	}
}

void URGBehaviorTreeBase::Init()
{

}

void URGBehaviorTreeBase::Reset()
{
	for (int i = 0; i < m_behaviorList.Num(); i++)
		m_behaviorList[i]->Reset();
	behaviorState = EBehaviorState::EB_Progress;
}

URGBehaviorTreeBase::~URGBehaviorTreeBase()
{
}

URGBehaviorTreeBase* URGBehaviorTreeBase::GetBehaviorTreeSegment(URGBehaviorTreeComponent* owner)
{
	return this;
}

EBehaviorState URGBehaviorTreeBase::Tick_Implementation(float deltaTime)
{
	behaviorState = EBehaviorState::EB_Progress;
	return EBehaviorState::EB_Progress;
}

void URGBehaviorTreeBase::AddPrintString(FString addString)
{
	UMoodComponent* moodComp = (UMoodComponent*)m_ownerComp->GetOwner()->GetComponentByClass(UMoodComponent::StaticClass());
	moodComp->AddThinkingString(addString);
}
