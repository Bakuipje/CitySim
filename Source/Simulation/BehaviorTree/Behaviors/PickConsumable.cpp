// Fill out your copyright notice in the Description page of Project Settings.

#include "PickConsumable.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"
#include "Agent.h"
#include "interactables/InteractableBase.h"
#include "InverntoryComponent.h"
#include "interactables/StorageBase.h"
UPickConsumable::UPickConsumable()
{
}
UPickConsumable::UPickConsumable(URGBehaviorTreeComponent* ownerComp, TArray<URGBehaviorTreeBase*>children, int cost, TSubclassOf<AInteractableBase> inventoryType)
	:URGBehaviorTreeBase(ownerComp, children,cost), m_invertoryType(inventoryType)
{
}

UPickConsumable::~UPickConsumable()
{
}
EBehaviorState UPickConsumable::Tick_Implementation(float deltaTime)
{
	AAgent* owner = (AAgent*)m_ownerComp->GetOwner();
	if (owner->currentStorage == nullptr)
	{
		behaviorState = EBehaviorState::EB_Failed;
		return behaviorState;
	}
	if (!owner->currentStorage->HasInteractable(m_invertoryType))
	{
		behaviorState = EBehaviorState::EB_Failed;
		return behaviorState;
	}
	UInverntoryComponent* inventory = (UInverntoryComponent*)owner->GetComponentByClass(UInverntoryComponent::StaticClass());
	inventory->AddInventroy(((AInvertoryBase*)owner->currentStorage->GetInteractable(m_invertoryType)), 1);
	owner->currentStorage->RemoveInteractable((m_invertoryType));
	behaviorState = EBehaviorState::EB_Succeed;
	return EBehaviorState::EB_Succeed;
}
