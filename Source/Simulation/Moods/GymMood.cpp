// Fill out your copyright notice in the Description page of Project Settings.

#include "GymMood.h"
#include "Agent.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"
#include "BehaviorTree/Behaviors/RGSelector.h"
#include "BehaviorTree/Behaviors/RGSequence.h"
#include "BehaviorTree/Behaviors/RGDomain.h"
#include "BehaviorTree/Behaviors/GymBehaviors/FindGym.h"
#include "BehaviorTree/Behaviors/GymBehaviors/GymBehavior.h"
#include "BehaviorTree/Behaviors/Transportation/MovementBehavior.h"

URGBehaviorTreeBase* UGymMood::GetBehaviorTree_Implementation(URGBehaviorTreeComponent* behviorTreeComponent)
{
	AAgent* owner = (AAgent*)behviorTreeComponent->GetOwner();
	behaviorTree = NewObject<URGSequence>();
	behaviorTree->m_cost = 3;

	UFindGym* findGym = NewObject<UFindGym>();
	UMovementBehavior* moveTo = NewObject<UMovementBehavior>();
	UGymBehavior* gymBehavior = NewObject<UGymBehavior>();

	behaviorTree->m_behaviorList.Add(findGym);
	behaviorTree->m_behaviorList.Add(moveTo->GetBehaviorTreeSegment(behviorTreeComponent));
	behaviorTree->m_behaviorList.Add(gymBehavior);

	behaviorTree->m_ownerComp = behviorTreeComponent;
	behaviorTree->BeginPlay();
	return behaviorTree;
}


