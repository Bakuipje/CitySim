// Fill out your copyright notice in the Description page of Project Settings.

#include "FoodBehavior.h"
#include "MoodComponent.h"
#include "RelationComponent.h"
#include "Moods/FoodMood.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"
#include "Building/House.h"
#include "Building/FoodPlace.h"
#include "Agent.h"


void UFoodBehavior::BeginPlay()
{
	foodTimer = foodDuration;
}

void UFoodBehavior::Reset()
{
	URGBehaviorTreeBase::Reset();
	foodTimer = foodDuration;
}

void UFoodBehavior::Init()
{
	AAgent* owner = (AAgent*)m_ownerComp->GetOwner();
	foodTimer = owner->foodPlace->waitTime;
}

EBehaviorState UFoodBehavior::Tick_Implementation(float deltaTime)
{
	if (foodTimer <= 0)
	{
		UMoodComponent* moodComp = (UMoodComponent*)m_ownerComp->GetOwner()->GetComponentByClass(UMoodComponent::StaticClass());
		URelationComponent* relationComp = (URelationComponent*)m_ownerComp->GetOwner()->GetComponentByClass(URelationComponent::StaticClass());
		AAgent* owner = (AAgent*)m_ownerComp->GetOwner();
		UMoodBase* currentMood = moodComp->GetMood(UFoodMood::StaticClass());
		m_ownerComp->RemoveMoodBehavior(currentMood->GetClass());
		moodComp->RemoveMood(currentMood->GetClass());
		owner->budget -= owner->foodPlace->cost;
		relationComp->foodMap[(int)owner->foodPlace->foodType]--;
		if(owner->homePlace!= nullptr)
			owner->homePlace->currentfood += owner->foodPlace->foodAmount;
		owner->foodPlace->AddRelationShips(owner, 0.3f, 0.1f);
		owner->foodPlace->RemoveVisitor(owner);
		owner->hungerStat = 0;
		AddPrintString(FString("Finished gathering food, Gained " + FString::FromInt(owner->foodPlace->foodAmount) + " food and paid " + FString::FromInt(owner->foodPlace->cost) + "units"));
		behaviorState = EBehaviorState::EB_Succeed;
		return behaviorState;
	}
	foodTimer -= deltaTime;
	behaviorState = EBehaviorState::EB_Progress;
	return behaviorState;
}

