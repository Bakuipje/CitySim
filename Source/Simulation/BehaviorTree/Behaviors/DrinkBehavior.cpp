// Fill out your copyright notice in the Description page of Project Settings.

#include "DrinkBehavior.h"
#include "BehaviorTree/RGBehaviorTreeBase.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"
#include "InverntoryComponent.h"
#include "interactables/DrinkBase.h"
#include "Moods/Thirst.h"
#include "MoodComponent.h"

UDrinkBehavior::UDrinkBehavior()
{
}

UDrinkBehavior::~UDrinkBehavior()
{
}

UDrinkBehavior::UDrinkBehavior(URGBehaviorTreeComponent* ownerComp, TArray<URGBehaviorTreeBase*> children, int cost)
	: URGBehaviorTreeBase(ownerComp, children, cost)
{
}

EBehaviorState UDrinkBehavior::Tick_Implementation(float deltaTime)
{
	UInverntoryComponent* inventory = (UInverntoryComponent*)m_ownerComp->GetOwner()->GetComponentByClass(UInverntoryComponent::StaticClass());
	UMoodComponent* moodComp = (UMoodComponent*)m_ownerComp->GetOwner()->GetComponentByClass(UMoodComponent::StaticClass());
	if (inventory->GetInventory(ADrinkBase::StaticClass()) <= 0)
	{
		behaviorState = EBehaviorState::EB_Failed;
		return EBehaviorState::EB_Failed;
	}
	inventory->RemoveInventory(ADrinkBase::StaticClass(), 1);
	m_ownerComp->RemoveMoodBehavior(UThirst::StaticClass());
	moodComp->RemoveMood(UThirst::StaticClass());
	behaviorState = EBehaviorState::EB_Succeed;
	return behaviorState;
}