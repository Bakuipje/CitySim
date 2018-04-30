// Fill out your copyright notice in the Description page of Project Settings.

#include "WorkMood.h"
#include "Agent.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"
#include "BehaviorTree/Behaviors/RGSelector.h"
#include "BehaviorTree/Behaviors/RGSequence.h"
#include "BehaviorTree/Behaviors/RGDomain.h"
#include "BehaviorTree/Behaviors/MoveToInteractable.h"
#include "BehaviorTree/Behaviors/WorkBehaviors/FindWork.h"
#include "BehaviorTree/Behaviors/WorkBehaviors/WorkBehavior.h"
#include "BehaviorTree/Behaviors/Transportation/MovementBehavior.h"
#include "BehaviorTree/Conditions/HasJob.h"



URGBehaviorTreeBase* UWorkMood::GetBehaviorTree_Implementation(URGBehaviorTreeComponent* behviorTreeComponent)
{
	AAgent* owner = (AAgent*)behviorTreeComponent->GetOwner();
	behaviorTree = NewObject<URGSelector>(URGSelector::StaticClass());
	behaviorTree->m_cost = 1;

	URGDomain* domain = NewObject<URGDomain>();
	UHasJob* jobCondition = NewObject<UHasJob>();
	domain->m_conditions.Add(jobCondition);

	URGSequence* WorkSequence = NewObject<URGSequence>();
	UMovementBehavior* moveToWork = NewObject<UMovementBehavior>();
	moveToWork->destinationActor = (AActor*&)owner->workPlace;
	UWorkBehavior* work = NewObject<UWorkBehavior>();
	work->workDuration = 10;
	work->compensation = 10;

	WorkSequence->m_behaviorList.Add(moveToWork->GetBehaviorTreeSegment(behviorTreeComponent));
	WorkSequence->m_behaviorList.Add(work);

	URGSequence* noWorkSequence = NewObject<URGSequence>();
	UFindWork* FindWork = NewObject<UFindWork>();
	UMovementBehavior* moveToNoWork = NewObject<UMovementBehavior>();
	moveToNoWork->destinationActor = ((AActor*&)owner->workPlace);
	UWorkBehavior* work2 = NewObject<UWorkBehavior>();
	work2->workDuration = 10;
	work2->compensation = 10;

	noWorkSequence->m_behaviorList.Add(FindWork);
	noWorkSequence->m_behaviorList.Add(moveToNoWork->GetBehaviorTreeSegment(behviorTreeComponent));
	noWorkSequence->m_behaviorList.Add(work2);

	domain->m_behaviorList.Add(WorkSequence);
	behaviorTree->m_behaviorList.Add(domain);
	behaviorTree->m_behaviorList.Add(noWorkSequence);
	// final intitialation
	behaviorTree->m_ownerComp = behviorTreeComponent;
	behaviorTree->BeginPlay();
	return behaviorTree;
}