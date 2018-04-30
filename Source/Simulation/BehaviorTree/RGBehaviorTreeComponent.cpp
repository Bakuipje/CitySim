// Fill out your copyright notice in the Description page of Project Settings.

#include "RGBehaviorTreeComponent.h"
#include "RGCondition.h"
#include "RGBehaviorTreeBase.h"
#include "Behaviors/RGSequence.h"
#include "Behaviors/RGSelector.h"
#include "Behaviors/RGQueue.h"
#include "Behaviors/RGRepeat.h"
#include "Behaviors/MoveToBehavior.h"
#include "Behaviors/RGDomain.h"
#include "Conditions/RGAtLocation.h"
#include "RGBlackBoard.h"
#include "Behaviors/RGTimer.h"
#include "Agent.h"
#include "Behaviors/MoveToInteractable.h"
#include "Behaviors/FindStorage.h"
#include "Moods/MoodBase.h"
// Sets default values for this component's properties
URGBehaviorTreeComponent::URGBehaviorTreeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	currentBehavior = nullptr;
	rootNode = nullptr;

	// ...
}


// Called when the game starts
void URGBehaviorTreeComponent::BeginPlay()
{
	Super::BeginPlay();
	blackBoard = (URGBlackBoard*)GetOwner()->GetComponentByClass(URGBlackBoard::StaticClass());
/*
	AAgent* agent = (AAgent*)GetOwner();
	currentBehavior = NewObject<URGSequence>(URGSequence::StaticClass());
	currentBehavior->m_cost = 10;
	UMoveToBehavior* move1behavior = NewObject<UMoveToBehavior>(UMoveToBehavior::StaticClass());
	move1behavior->m_destination = FVector(0, 1000, 0);
	move1behavior->m_range = 100.0f;
	UMoveToBehavior* mov2behavior = NewObject<UMoveToBehavior>(UMoveToBehavior::StaticClass());
	mov2behavior->m_destination = FVector(1000, 1000, 0);
	mov2behavior->m_range = 100.0f;
	URGTimer* timer = NewObject<URGTimer>(URGTimer::StaticClass());
	timer->m_time = 4.0f;
	UMoveToBehavior* move3behavior = NewObject<UMoveToBehavior>(UMoveToBehavior::StaticClass());
	move3behavior->m_destination = FVector(1000, 0, 0);
	move3behavior->m_range = 100.0f;

	UMoveToBehavior* mov4behavior = NewObject<UMoveToBehavior>(UMoveToBehavior::StaticClass());
	mov4behavior->m_destination = FVector(0, 0, 0);
	mov4behavior->m_range = 100.0f;
	currentBehavior->m_behaviorList.Add(move1behavior);
	currentBehavior->m_behaviorList.Add(mov2behavior);
	currentBehavior->m_behaviorList.Add(timer);
	currentBehavior->m_behaviorList.Add(move3behavior);
	currentBehavior->m_behaviorList.Add(mov4behavior);*/

	rootNode = NewObject<URGQueue>(URGQueue::StaticClass()); 
	//rootNode->m_behaviorList.Add(currentBehavior);
	rootNode->m_ownerComp = this;
	rootNode->m_parent = nullptr;
	rootNode->BeginPlay();
	// ...

}


// Called every frame
void URGBehaviorTreeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsValid(currentBehavior))
	{
		EBehaviorState currentState = currentBehavior->Tick(DeltaTime);
		if (currentState == EBehaviorState::EB_Succeed || currentState == EBehaviorState::EB_Failed)
		{
			if (currentBehavior == rootNode)
			{
				rootNode->Reset();
			}
			else currentBehavior = currentBehavior->m_parent;
		}
	}
	else currentBehavior = rootNode;
	if (dirty)
	{
		currentBehavior = tempBehavior;
		currentBehavior->Init();
		dirty = false;
	}
}

void URGBehaviorTreeComponent::SetCurrentBehavior(URGBehaviorTreeBase* behavior)
{
	tempBehavior = behavior;
	dirty = true;
}

URGBlackBoard* URGBehaviorTreeComponent::GetBlackBoard()
{
	return blackBoard;
}
URGBehaviorTreeBase* URGBehaviorTreeComponent::GetBehaviorTree()
{
	return currentBehavior;
}

URGBehaviorTreeBase* URGBehaviorTreeComponent::GetRootNode()
{
	return rootNode;
}

void URGBehaviorTreeComponent::AddMoodBehavior(UMoodBase* mood)
{
	if (m_moodBehaviors.Contains(mood->GetClass()))
		return;
	m_moodBehaviors.Add(mood->GetClass(), mood->GetBehaviorTree(this));
	m_moodBehaviors[mood->GetClass()]->m_parent = rootNode;
	m_moodBehaviors[mood->GetClass()]->BeginPlay();
	rootNode->m_behaviorList.Add(m_moodBehaviors[mood->GetClass()]);

	
}

void URGBehaviorTreeComponent::RemoveMoodBehavior(TSubclassOf<UMoodBase> moodType)
{
	if (!m_moodBehaviors.Contains(moodType))
		return;
	rootNode->m_behaviorList.Remove(m_moodBehaviors[moodType]);
	m_moodBehaviors.Remove(moodType);

}

void URGBehaviorTreeComponent::AbbortBehaviors()
{
	currentBehavior->behaviorState = EBehaviorState::EB_Failed;
	currentBehavior = rootNode;
}