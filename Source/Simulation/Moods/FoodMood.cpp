// Fill out your copyright notice in the Description page of Project Settings.

#include "FoodMood.h"
#include "Agent.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"
#include "BehaviorTree/Behaviors/RGSelector.h"
#include "BehaviorTree/Behaviors/RGSequence.h"
#include "BehaviorTree/Behaviors/RGDomain.h"
#include "BehaviorTree/Behaviors/MoveToInteractable.h"
#include "BehaviorTree/Behaviors/FoodBehaviors/FindFood.h"
#include "BehaviorTree/Behaviors/FoodBehaviors/FoodBehavior.h"
#include "BehaviorTree/Behaviors/FoodBehaviors/FailedFood.h"
#include "BehaviorTree/Behaviors/Transportation/MovementBehavior.h"



URGBehaviorTreeBase* UFoodMood::GetBehaviorTree_Implementation(URGBehaviorTreeComponent* behviorTreeComponent)
{
	AAgent* owner = (AAgent*)behviorTreeComponent->GetOwner();
	behaviorTree = NewObject < URGSelector > (URGSelector::StaticClass());
	behaviorTree->m_cost = 2;
	
	URGSequence* sequence = NewObject<URGSequence>();
	UFindFood* findFood = NewObject<UFindFood>();
	UMovementBehavior* moveToFoodPlace = NewObject<UMovementBehavior>();
	//moveToFoodPlace->m_destinationObject = (AActor*&)owner->foodPlace;
	UFoodBehavior* foodBehavior = NewObject<UFoodBehavior>();
	foodBehavior->foodDuration = 10;
	sequence->m_behaviorList.Add(findFood);
	sequence->m_behaviorList.Add(moveToFoodPlace->GetBehaviorTreeSegment(behviorTreeComponent));
	sequence->m_behaviorList.Add(foodBehavior);
	UFailedFood* failedFood = NewObject<UFailedFood>();
	failedFood->stressAmount = 3;

	behaviorTree->m_behaviorList.Add(sequence);
	behaviorTree->m_behaviorList.Add(failedFood);
	// final initialization
	behaviorTree->m_ownerComp = behviorTreeComponent;
	behaviorTree->BeginPlay();
	return behaviorTree;
}