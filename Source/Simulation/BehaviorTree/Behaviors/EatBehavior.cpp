// Fill out your copyright notice in the Description page of Project Settings.

#include "EatBehavior.h"
#include "BehaviorTree/RGBehaviorTreeBase.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"
#include "InverntoryComponent.h"
#include "interactables/FoodBase.h"
#include "Moods/Hunger.h"
#include "MoodComponent.h"
#include "Moods/MoodBase.h"

UEatBehavior::UEatBehavior()
{
}

UEatBehavior::UEatBehavior(URGBehaviorTreeComponent* ownerComp, TArray<URGBehaviorTreeBase*> children, int cost)
	: URGBehaviorTreeBase(ownerComp, children, cost)
{
}

UEatBehavior::~UEatBehavior()
{
}

EBehaviorState UEatBehavior::Tick_Implementation(float deltaTime)
{
	UInverntoryComponent* inventory = (UInverntoryComponent*)m_ownerComp->GetOwner()->GetComponentByClass(UInverntoryComponent::StaticClass());
	UMoodComponent* moodComp = (UMoodComponent*)m_ownerComp->GetOwner()->GetComponentByClass(UMoodComponent::StaticClass());
	if (inventory->GetInventory(AFoodBase::StaticClass()) <= 0)
	{
		behaviorState = EBehaviorState::EB_Failed;
		return EBehaviorState::EB_Failed;
	}
	inventory->RemoveInventory(AFoodBase::StaticClass(), 1);
	UMoodBase* currentMood = moodComp->GetMood(UHunger::StaticClass());
	if(currentMood == nullptr)
		currentMood=moodComp->GetMood(m_moodType);
	m_ownerComp->RemoveMoodBehavior(currentMood->GetClass());
	moodComp->RemoveMood(currentMood->GetClass());
	behaviorState = EBehaviorState::EB_Succeed;
	return behaviorState;
}