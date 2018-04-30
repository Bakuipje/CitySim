// Fill out your copyright notice in the Description page of Project Settings.

#include "Thirst.h"
#include "Agent.h"

#include "BehaviorTree/RGBehaviorTreeComponent.h"
#include "BehaviorTree/Behaviors/RGSelector.h"
#include "BehaviorTree/Behaviors/RGSequence.h"
					   
#include "BehaviorTree/Behaviors/RGDomain.h"
#include "BehaviorTree/Behaviors/DrinkBehavior.h"
#include "BehaviorTree/Behaviors/FindConsumable.h"
#include "BehaviorTree/Behaviors/MoveToInteractable.h"
#include "BehaviorTree/Behaviors/PickConsumable.h"
#include "BehaviorTree/Behaviors/RGTimer.h"

#include "interactables/DrinkBase.h"


URGBehaviorTreeBase* UThirst::GetBehaviorTree_Implementation(URGBehaviorTreeComponent* behaviorTreeComponent)
{
	AAgent* owner = (AAgent*)behaviorTreeComponent->GetOwner();
	behaviorTree = NewObject<URGSelector>(URGSelector::StaticClass());
	behaviorTree->m_cost = 1;
	UDrinkBehavior* drinkbehavior = NewObject<UDrinkBehavior>(UDrinkBehavior::StaticClass());
	URGSequence* sequence = NewObject<URGSequence>(URGSequence::StaticClass());
	sequence->m_cost = 1;
	UFindConsumable* findConsumable = NewObject<UFindConsumable>(UFindConsumable::StaticClass());
	findConsumable->m_invertoryType = ADrinkBase::StaticClass();
	findConsumable->m_range = 1000;
	UMoveToInteractable* moveToInteractable = NewObject<UMoveToInteractable>(UMoveToInteractable::StaticClass());
	moveToInteractable->m_destinationObject = (AActor*&)owner->currentStorage;
	moveToInteractable->m_range = 200;
	UPickConsumable* pickConsumable = NewObject<UPickConsumable>(UPickConsumable::StaticClass());
	pickConsumable->m_invertoryType = ADrinkBase::StaticClass();
	UDrinkBehavior* eatsequencedBehavior = NewObject<UDrinkBehavior>(UDrinkBehavior::StaticClass());
	URGTimer* timer = NewObject<URGTimer>(URGTimer::StaticClass());
	timer->m_time = 4.0f;
	behaviorTree->m_behaviorList.Add(drinkbehavior);
	behaviorTree->m_behaviorList.Add(sequence);
	sequence->m_behaviorList.Add(findConsumable);
	sequence->m_behaviorList.Add(moveToInteractable);
	sequence->m_behaviorList.Add(pickConsumable);
	sequence->m_behaviorList.Add(eatsequencedBehavior);
	sequence->m_behaviorList.Add(timer);
	behaviorTree->m_ownerComp = behaviorTreeComponent;

	behaviorTree->BeginPlay();
	return behaviorTree;
}

