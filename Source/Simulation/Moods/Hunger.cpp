// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunger.h"
#include "Agent.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"
#include "BehaviorTree/Behaviors/RGSelector.h"
#include "BehaviorTree/Behaviors/RGSequence.h"
					   
#include "BehaviorTree/Behaviors/RGDomain.h"
#include "BehaviorTree/Behaviors/EatBehavior.h"
#include "BehaviorTree/Behaviors/FindConsumable.h"
#include "BehaviorTree/Behaviors/MoveToInteractable.h"
#include "BehaviorTree/Behaviors/PickConsumable.h"
#include "BehaviorTree/Behaviors/RGTimer.h"

#include "interactables/FoodBase.h"
UHunger::UHunger()
{
}

UHunger::~UHunger()
{
}

URGBehaviorTreeBase* UHunger::GetBehaviorTree_Implementation(URGBehaviorTreeComponent* behaviorTreeComponent)
{
	AAgent* owner = (AAgent*)behaviorTreeComponent->GetOwner();
	
	behaviorTree = NewObject<URGSelector>(URGSelector::StaticClass());
	behaviorTree->m_cost = 2;
	UEatBehavior* eatbehavior = NewObject<UEatBehavior>(UEatBehavior::StaticClass());
	URGSequence* sequence = NewObject<URGSequence>(URGSequence::StaticClass());
	UFindConsumable* findConsumable = NewObject<UFindConsumable>(UFindConsumable::StaticClass());
	findConsumable->m_invertoryType = AFoodBase::StaticClass();
	findConsumable->m_range = 1000;
	UMoveToInteractable* moveToInteractable = NewObject<UMoveToInteractable>(UMoveToInteractable::StaticClass());
	moveToInteractable->m_destinationObject = ((AActor*&)owner->currentStorage);
	moveToInteractable->m_range = 200;
	UPickConsumable* pickConsumable = NewObject<UPickConsumable>(UPickConsumable::StaticClass());
	pickConsumable->m_invertoryType = AFoodBase::StaticClass();
	UEatBehavior* eatsequencedBehavior = NewObject<UEatBehavior>(UEatBehavior::StaticClass());
	URGTimer* timer = NewObject<URGTimer>(URGTimer::StaticClass());
	timer->m_time = 4.0f;
	behaviorTree->m_behaviorList.Add(eatbehavior);
	behaviorTree->m_behaviorList.Add(sequence);
	sequence->m_behaviorList.Add(findConsumable);
	sequence->m_behaviorList.Add(moveToInteractable);
	sequence->m_behaviorList.Add(pickConsumable);
	sequence->m_behaviorList.Add(eatsequencedBehavior);
	sequence->m_behaviorList.Add(timer);
		/*RGSelector(behaviorTreeComponent,
		TArray<URGBehaviorTreeBase*>
	{
		new EatBehavior(behaviorTreeComponent, TArray<URGBehaviorTreeBase*>(), 0),
			new URGSequence(behaviorTreeComponent, TArray<URGBehaviorTreeBase*>
		{
			new UFindConsumable(behaviorTreeComponent, TArray<URGBehaviorTreeBase*>(), 0, AFoodBase::StaticClass(), 1000),
				new  UMoveToInteractable(behaviorTreeComponent, TArray<URGBehaviorTreeBase*>(), 0, &owner->currentStorage, 200),
				new UPickConsumable(behaviorTreeComponent, TArray<URGBehaviorTreeBase*>(), 0, AFoodBase::StaticClass()),
				new EatBehavior(behaviorTreeComponent, TArray<URGBehaviorTreeBase*>(), 0),
				new URGTimer(behaviorTreeComponent, TArray<URGBehaviorTreeBase*>(),0,4.0f)

		}, 0)
	},
		2

				);*/
	behaviorTree->m_ownerComp = behaviorTreeComponent;
	behaviorTree->BeginPlay();
	return behaviorTree;
}