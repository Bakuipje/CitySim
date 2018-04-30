// Fill out your copyright notice in the Description page of Project Settings.

#include "HomeMood.h"
#include "Agent.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"
#include "BehaviorTree/Behaviors/RGSelector.h"
#include "BehaviorTree/Behaviors/RGSequence.h"
#include "BehaviorTree/Behaviors/RGDomain.h"
#include "BehaviorTree/Behaviors/MoveToInteractable.h"
#include "BehaviorTree/Behaviors/Home/FindHome.h"
#include "BehaviorTree/Behaviors/Home/HomeBehavior.h"
#include "BehaviorTree/Behaviors/Transportation/MovementBehavior.h"

#include "BehaviorTree/Conditions/HasHome.h"

URGBehaviorTreeBase* UHomeMood::GetBehaviorTree_Implementation(URGBehaviorTreeComponent* behviorTreeComponent)
{
	AAgent* owner = (AAgent*)behviorTreeComponent->GetOwner();
	behaviorTree = NewObject<URGSelector>(URGSelector::StaticClass());
	behaviorTree->m_cost = 5;

	URGDomain* domain = NewObject<URGDomain>();
	UHasHome* homeCondition = NewObject<UHasHome>();
	domain->m_conditions.Add(homeCondition);

	URGSequence* homeSequence = NewObject<URGSequence>();
	UMovementBehavior* moveToHome = NewObject<UMovementBehavior>();
	UHomeBehavior* home = NewObject<UHomeBehavior>();
	home->homeDuration = 10;
	homeSequence->m_behaviorList.Add(moveToHome->GetBehaviorTreeSegment(behviorTreeComponent));
	homeSequence->m_behaviorList.Add(home);

	URGSequence* noHomeSequence = NewObject<URGSequence>();
	UFindHome* findHome = NewObject<UFindHome>();
	UMovementBehavior* moveToNewHome = NewObject<UMovementBehavior>();
	UHomeBehavior* newHome = NewObject<UHomeBehavior>();
	newHome->homeDuration = 10;
	noHomeSequence->m_behaviorList.Add(findHome);
	noHomeSequence->m_behaviorList.Add(moveToNewHome->GetBehaviorTreeSegment(behviorTreeComponent));
	noHomeSequence->m_behaviorList.Add(newHome);

	domain->m_behaviorList.Add(homeSequence);
	behaviorTree->m_behaviorList.Add(domain);
	behaviorTree->m_behaviorList.Add(noHomeSequence);

	behaviorTree->m_ownerComp = behviorTreeComponent;
	behaviorTree->BeginPlay();
	return behaviorTree;
}

