// Fill out your copyright notice in the Description page of Project Settings.

#include "RGDomain.h"
#include "BehaviorTree/RGBehaviorTreeBase.h"
#include "BehaviorTree/RGCondition.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"

URGDomain::URGDomain()
{
}

/*
URGDomain::URGDomainURGDomainURGBehaviorTreeComponent* ownerComp,  TArray<URGBehaviorTreeBase*> children,int cost, TArray<RGCondition*>conditions)
	:URGBehaviorTreeBase(ownerComp,  children,  cost) , m_conditions(conditions)
{
	m_checkedConditions = false;
}*/

URGDomain::~URGDomain()
{
}

void URGDomain::Reset()
{
	URGBehaviorTreeBase::Reset();
	m_checkedConditions = false;
}

void URGDomain::BeginPlay()
{
	URGBehaviorTreeBase::BeginPlay();
	for (int i=0; i< m_conditions.Num(); i++)
	{
		m_conditions[i]->m_ownerComp = m_ownerComp;
	}
}

EBehaviorState URGDomain::Tick_Implementation(float deltaTime)
{
	if (!m_checkedConditions)
	{
		for (int i = 0; i < m_conditions.Num(); i++)
		{
			if (!m_conditions[i]->Execute())
			{
				behaviorState = EBehaviorState::EB_Failed;
				return behaviorState;
			}
		}
		m_checkedConditions = true;
	}
	for (int i = 0; i < m_behaviorList.Num(); i++)
	{
		behaviorState = m_behaviorList[i]->behaviorState;

		if(behaviorState == EBehaviorState::EB_Progress)
		m_ownerComp->SetCurrentBehavior(m_behaviorList[i]);

		return behaviorState;
	}
	behaviorState = EBehaviorState::EB_Succeed;
	return behaviorState;

}