// Fill out your copyright notice in the Description page of Project Settings.

#include "AngryMood.h"
#include "Agent.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"
#include "BehaviorTree/Behaviors/RGSelector.h"
#include "BehaviorTree/Behaviors/RGSequence.h"
#include "BehaviorTree/Behaviors/RGDomain.h"
#include "BehaviorTree/Behaviors/MoveToInteractable.h"
#include "BehaviorTree/Behaviors/AgentBehaviors/AngryBehavior.h"


URGBehaviorTreeBase* UAngryMood::GetBehaviorTree_Implementation(URGBehaviorTreeComponent* behviorTreeComponent)
{
	AAgent* owner = (AAgent*)behviorTreeComponent->GetOwner();
	behaviorTree = NewObject < URGSelector >(URGSelector::StaticClass());
	behaviorTree->m_cost = 1;
	URGSequence* sequence = NewObject<URGSequence>();
	UAngryBehavior* angry = NewObject<UAngryBehavior>();
	angry->stressAmount = 3;
	angry->argueTime = 5;
	angry->target = target;
	sequence->m_behaviorList.Add(angry);

	behaviorTree->m_behaviorList.Add(sequence);
	behaviorTree->m_ownerComp = behviorTreeComponent;
	behaviorTree->BeginPlay();
	return behaviorTree;

}

void UAngryMood::SetTarget(AAgent* targetAgent)
{
	target = targetAgent;
}

