// Fill out your copyright notice in the Description page of Project Settings.

#include "HasConsumable.h"
#include "Agent.h"
#include "BehaviorTree/RGBehaviorTreeComponent.h"
#include "InverntoryComponent.h"

UHasConsumable::UHasConsumable()
{
}

UHasConsumable::~UHasConsumable()
{
}

UHasConsumable::UHasConsumable(URGBehaviorTreeComponent* ownerComp, TSubclassOf<AInvertoryBase> inverntoryType)
	:URGCondition(ownerComp), m_inventoryType(inverntoryType)
{}
bool UHasConsumable::Execute_Implementation()
{
	AAgent* owner = (AAgent*)m_ownerComp->GetOwner();
	UInverntoryComponent* invertoryComp = (UInverntoryComponent*)owner->GetComponentByClass(UInverntoryComponent::StaticClass());
	return invertoryComp->GetInventory(m_inventoryType)>0;
}
