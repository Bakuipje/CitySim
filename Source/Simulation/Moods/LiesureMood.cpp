// Fill out your copyright notice in the Description page of Project Settings.

#include "LiesureMood.h"
#include "Agent.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"
#include "BehaviorTree/Behaviors/RGSelector.h"
#include "BehaviorTree/Behaviors/RGSequence.h"
#include "BehaviorTree/Behaviors/RGDomain.h"
#include "BehaviorTree/Behaviors/MoveToInteractable.h"
#include "BehaviorTree/Behaviors/LiesureBehaviors/FindLiesurePlace.h"
#include "BehaviorTree/Behaviors/LiesureBehaviors/LiesureBehavior.h"
#include "BehaviorTree/Behaviors/Transportation/MovementBehavior.h"

#include "BehaviorTree/Conditions/HasLiesurePlace.h"

URGBehaviorTreeBase* ULiesureMood::GetBehaviorTree_Implementation(URGBehaviorTreeComponent* behviorTreeComponent)
{
	AAgent* owner = (AAgent*)behviorTreeComponent->GetOwner();
	behaviorTree = NewObject<URGSequence>(URGSequence::StaticClass());
	behaviorTree->m_cost = 5;

	UFindLiesurePlace* findHome = NewObject<UFindLiesurePlace>();
	UMovementBehavior* moveToNewHome = NewObject<UMovementBehavior>();
	ULiesureBehavior* newHome = NewObject<ULiesureBehavior>();
	newHome->liesureDuration = 10;
	behaviorTree->m_behaviorList.Add(findHome);
	behaviorTree->m_behaviorList.Add(moveToNewHome->GetBehaviorTreeSegment(behviorTreeComponent));
	behaviorTree->m_behaviorList.Add(newHome);

	behaviorTree->m_ownerComp = behviorTreeComponent;
	behaviorTree->BeginPlay();
	return behaviorTree;
}


